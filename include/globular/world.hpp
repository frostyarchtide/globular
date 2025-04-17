#pragma once

#include "entity.hpp"

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <queue>
#include <vector>

struct Component {};

class IComponents {
public:
    virtual ~IComponents() = default;

    virtual size_t size() const = 0;
    virtual Entity get_owner(size_t index) const = 0;
    virtual void remove(size_t index) = 0;
};

template <typename T>
class Components : public IComponents {
public:
    std::vector<T> data;
    std::vector<Entity> owners;

    Components() {}

    size_t size() const {
        return data.size();
    }

    Entity get_owner(size_t index) const {
        return owners[index];
    }

    void remove(size_t index) {
        data[index] = data.back();
        data.pop_back();
        owners[index] = owners.back();
        owners.pop_back();
    }
};

class World {
public:
    World() {}

    Entity create_entity();
    bool destroy_entity(Entity entity);

    template <typename T, typename... Args>
    bool add_component(Entity entity, Args&&... args) {
        auto entity_iter = entities.find(entity);
        if (
               entity_iter == entities.end()
            || entity_iter->second.find(typeid(T)) != entity_iter->second.end()
        )
            return false;

        auto component_iter = components.find(typeid(T));
        if (component_iter == components.end()) {
            components.emplace(
                typeid(T),
                std::make_unique<Components<T>>()
            );
        }

        Components<T>* components_collection = (Components<T>*) components[typeid(T)].get();
        components_collection->data.push_back(T(args...));
        components_collection->owners.push_back(entity);

        entity_iter->second.emplace(
            typeid(T),
            components_collection->size() - 1
        );

        return true;
    }

    template <typename T>
    bool remove_component(Entity entity) {
        auto entity_iter = entities.find(entity);
        if (entity_iter == entities.end()) return false;

        Components<T>* components_collection = (Components<T>*) components[typeid(T)].get();
        Entity owner = components_collection->get_owner(components_collection->size() - 1);
        size_t index = entity_iter->second[typeid(T)];

        components_collection->remove(index);
        entities[owner][typeid(T)] = index;
        entity_iter->second.erase(typeid(T));

        return true;
    }

    template <typename T>
    T* get_component(Entity entity) {
        auto entity_iter = entities.find(entity);
        if (entity_iter == entities.end()) return nullptr;
        
        auto component_iter = entity_iter->second.find(typeid(T));
        if (component_iter == entity_iter->second.end()) return nullptr;

        return &((Components<T>*) components[typeid(T)].get())
            ->data[component_iter->second];
    }

    template <typename T>
    std::vector<T*> get_components() {
        auto component_iter = components.find(typeid(T));
        if (component_iter == components.end()) return {};

        std::vector<T*> vector;
        for (T& component : ((Components<T>*) component_iter->second.get())->data) {
            vector.push_back(&component);
        }

        return vector;
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<IComponents>> components;
    std::unordered_map<Entity, std::unordered_map<std::type_index, size_t>> entities;
    uint32_t next_id = 0;
    std::queue<uint32_t> available_ids;
    std::unordered_map<uint32_t, uint32_t> generations;
};
