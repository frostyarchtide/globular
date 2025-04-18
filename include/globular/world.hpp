#pragma once

#include "entity.hpp"
#include "containers/sparse_set.hpp"

#include <algorithm>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <queue>

struct Component {};

class IComponents {
public:
    virtual ~IComponents() = default;

    virtual bool remove(size_t index) = 0;
};

template <typename T>
class Components : public IComponents {
public:
    SparseSet<T> data;

    bool remove(size_t index) { return data.remove(index); }
};

class World {
public:
    Entity create_entity();
    bool destroy_entity(Entity entity);
    bool contains_entity(Entity entity);

    template <typename T, typename... Args>
    bool add_component(Entity entity, Args&&... args) {
        auto entities_iter = entities.find(entity);
        if (entities_iter == entities.end()) return false;

        auto component_iter = std::find(
            entities_iter->second.begin(),
            entities_iter->second.end(),
            typeid(T)
        );
        if (component_iter != entities_iter->second.end()) return false;

        auto components_iter = components.find(typeid(T));
        if (components_iter == components.end()) {
            components.emplace(typeid(T), std::make_unique<Components<T>>());
            components_iter = components.find(typeid(T));
        }

        if (!((Components<T>*) components_iter->second.get())->data.add(entity.id, T(args...))) return false;

        entities_iter->second.push_back(typeid(T));

        return true;
    }

    template <typename T>
    bool remove_component(Entity entity) {
        auto entities_iter = entities.find(entity);
        if (entities_iter == entities.end()) return false;

        auto component_iter = std::find(
            entities_iter->second.begin(),
            entities_iter->second.end(),
            typeid(T)
        );
        if (component_iter == entities_iter->second.end()) return false;

        auto components_iter = components.find(typeid(T));
        if (components_iter == components.end()) return false;

        if (!((Components<T>*) components_iter->second.get())->data.remove(entity.id)) return false;

        entities_iter->second.erase(component_iter);

        return true;
    }

    template <typename T>
    T* get_component(Entity entity) {
        auto entities_iter = entities.find(entity);
        if (entities_iter == entities.end()) return nullptr;

        auto component_iter = std::find(
            entities_iter->second.begin(),
            entities_iter->second.end(),
            typeid(T)
        );
        if (component_iter == entities_iter->second.end()) return nullptr;

        auto components_iter = components.find(typeid(T));
        if (components_iter == components.end()) return nullptr;

        if (!((Components<T>*) components_iter->second.get())->data.contains(entity.id)) return nullptr;

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
    std::unordered_map<Entity, std::vector<std::type_index>> entities;
    uint32_t next_id = 0;
    std::queue<uint32_t> available_ids;
    std::unordered_map<uint32_t, uint32_t> generations;
};
