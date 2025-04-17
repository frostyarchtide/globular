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

    virtual size_t get_size() = 0;
    virtual Entity get_owner(size_t index) = 0;
    virtual void remove(size_t index) = 0;
};

template <typename T>
class Components : public IComponents {
public:
    std::vector<T> data;
    std::vector<Entity> owners;

    Components() {}

    size_t get_size() {
        return data.size();
    }

    Entity get_owner(size_t index) {
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
    void destroy_entity(Entity entity);

    template <typename T, typename... Args>
    bool insert_component(Entity entity, Args&&... args) {
        auto entity_iterator = entities.find(entity);
        if (entity_iterator == entities.end()) return false;
        if (entity_iterator->second.find(typeid(T)) != entity_iterator->second.end()) return false;

        auto component_iterator = components.find(typeid(T));
        if (component_iterator == components.end()) {
            components.emplace(
                typeid(T),
                std::make_unique<Components<T>>()
            );
        }

        Components<T>* components_collection = (Components<T>*) components[typeid(T)].get();
        components_collection->data.push_back(T(args...));
        components_collection->owners.push_back(entity);

        auto entity_component_iterator = entity_iterator->second.find(typeid(T));
        if (entity_component_iterator == entity_iterator->second.end()) {
            entity_iterator->second.emplace(
                typeid(T),
                components_collection->data.size() - 1
            );
        }

        return true;
    }

    template <typename T>
    void remove_component(Entity entity) {
        auto entity_iterator = entities.find(entity);
        if (entity_iterator == entities.end()) return;

        auto components_collection = components[typeid(T)].get();
        Entity owner = components_collection->get_owner(components_collection->get_size() - 1);
        size_t index = entity_iterator->second[typeid(T)];
        components_collection->remove(index);
        entities[owner][typeid(T)] = index;
        entity_iterator->second.erase(typeid(T));
    }

    template <typename T>
    T* get_component(Entity entity) {
        auto entity_iterator = entities.find(entity);
        if (entity_iterator == entities.end()) return nullptr;
        
        auto component_iterator = entity_iterator->second.find(typeid(T));
        if (component_iterator == entity_iterator->second.end()) return nullptr;

        return &((Components<T>*) components[typeid(T)].get())
            ->data[component_iterator->second];
    }

    template <typename T>
    std::vector<T*> get_components() {
        auto iterator = components.find(typeid(T));
        if (iterator == components.end()) return {};

        std::vector<T*> vector;

        for (T& component : ((Components<T>*) iterator->second.get())->data) {
            vector.push_back(&component);
        }

        return vector;
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<IComponents>> components;
    uint32_t next_id = 0;
    std::queue<uint32_t> available_ids;
    std::unordered_map<uint32_t, uint32_t> generations;
    std::unordered_map<Entity, std::unordered_map<std::type_index, size_t>> entities;
};
