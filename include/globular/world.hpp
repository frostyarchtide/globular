#pragma once

#include "entity.hpp"
#include "containers/sparse_set.hpp"

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <queue>

struct Component {};

class IComponents {
public:
    virtual ~IComponents() = default;
};

template <typename T>
class Components : public IComponents {
public:
    SparseSet<T> data;
};

class World {
public:
    Entity create_entity();
    bool destroy_entity(Entity entity);
    bool contains_entity(Entity entity);

    template <typename T, typename... Args>
    bool add_component(Entity entity, Args&&... args) {
        if (!contains_entity(entity)) return false;

        auto components_iter = components.find(typeid(T));
        if (components_iter == components.end()) {
            components.emplace(typeid(T), std::make_unique<Components<T>>());
            components_iter = components.find(typeid(T));
        }

        if (!((Components<T>*) components_iter->second.get())->data.add(entity.id, T(args...))) return false;

        return true;
    }

    template <typename T>
    bool remove_component(Entity entity) {
        if (!contains_entity(entity)) return false;

        auto components_iter = components.find(typeid(T));
        if (components_iter == components.end()) return false;

        if (!((Components<T>*) components_iter->second.get())->data.contains(entity.id)) return false;

        return ((Components<T>*) components_iter->second.get())->data[entity.id];
    }

    template <typename T>
    T* get_component(Entity entity) {
        if (!contains_entity(entity)) return false;

        auto components_iter = components.find(typeid(T));
        if (components_iter == components.end()) return nullptr;

        return &((Components<T>*) components_iter->second.get())->data[entity.id];
    }

    template <typename T>
    std::vector<T*> get_components() {
        std::vector<T*> vector;

        auto components_iter = components.find(typeid(T));
        if (components_iter == components.end()) return vector;

        for (auto& component : ((Components<T>*) components_iter->second.get())->data.get_elements()) {
            vector.push_back(&component);
        }

        return vector;
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<IComponents>> components;
    std::unordered_set<Entity> entities;
    uint32_t next_id = 0;
    std::queue<uint32_t> available_ids;
    std::unordered_map<uint32_t, uint32_t> generations;
};
