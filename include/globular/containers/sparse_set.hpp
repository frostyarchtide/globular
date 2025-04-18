#pragma once

#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>
#include <iostream>

template <typename T, size_t page_size = 1024>
class SparseSet {
public:
    size_t size() const {
        return total_size;
    }

    bool contains(size_t index) const {
        size_t page = index / page_size;
        size_t page_index = index % page_size;

        return page < sparse.size()
            && sparse[page]
            && (*sparse[page])[page_index].has_value();
    }

    bool add(size_t index, const T& value) {
        size_t page = index / page_size;

        if (page >= sparse.size()) {
            sparse.resize(page + 1);
        }

        if (!sparse[page]) {
            sparse[page] = std::make_unique<std::array<std::optional<size_t>, page_size>>();
        }

        size_t page_index = index % page_size;

        if ((*sparse[page])[page_index]) return false;

        (*sparse[page])[page_index] = dense.size();
        dense.push_back(value);
        reverse_sparse.push_back(index);
        total_size++;

        return true;
    }

    bool remove(size_t index) {
        if (!contains(index)) return false;

        size_t page = index / page_size;
        size_t page_index = index % page_size;

        size_t dense_index = (*sparse[page])[page_index].value();

        if (dense_index != dense.size() - 1) {
            dense[dense_index] = std::move(dense.back());

            size_t previous_index = reverse_sparse[dense.size() - 1];
            size_t previous_page = previous_index / page_size;
            size_t previous_page_index = previous_index % page_size;

            (*sparse[previous_page])[previous_page_index] = dense_index;
            reverse_sparse[dense_index] = previous_index;
        }

        (*sparse[page])[page_index] = std::nullopt;

        dense.pop_back();
        reverse_sparse.pop_back();
        total_size--;

        return true;
    }

    std::vector<T>& get_elements() {
        return dense;
    }

    T& operator[](size_t index) {
        if (!contains(index)) throw std::out_of_range("Index out of bounds");

        return dense[(*sparse[index / page_size])[index % page_size].value()];
    }

private:
    std::vector<T> dense;
    std::vector<std::unique_ptr<std::array<std::optional<size_t>, page_size>>> sparse;
    std::vector<size_t> reverse_sparse;
    size_t total_size = 0;
};
