#include "globular/world.hpp"

Entity World::create_entity() {
    uint32_t id;
    uint32_t generation = 0;

    if (available_ids.empty()) {
        id = next_id++;
    } else {
        id = available_ids.front();
        available_ids.pop();
        generation = generations[id]++;
    }

    Entity entity(this, id, generation);

    entities[entity] = std::unordered_map<std::type_index, size_t>();

    return entity;
}

void World::destroy_entity(Entity entity) {
    auto entity_iterator = entities.find(entity);
    if (entity_iterator == entities.end()) return;

    available_ids.push(entity.id);
    
    auto generation_iterator = generations.find(entity.id);
    if (generation_iterator == generations.end()) {
        generations.emplace(entity.id, 1);
    } else {
        generation_iterator->second++;
    }

    for (auto& [type, index] : entity_iterator->second) {
        auto components_collection = components[type].get();
        Entity owner = components_collection->get_owner(components_collection->get_size() - 1);
        components_collection->remove(index);
        entities[owner][type] = index;
    }

    entities.erase(entity);
}
