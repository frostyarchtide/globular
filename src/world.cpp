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

    Entity entity(id, generation);
    entities.emplace(
        entity,
        std::unordered_map<std::type_index, size_t>()
    );

    return entity;
}

bool World::destroy_entity(Entity entity) {
    auto entity_iter = entities.find(entity);
    if (entity_iter == entities.end()) return false;

    available_ids.push(entity.id);

    auto generation_iter = generations.find(entity.id);
    if (generation_iter == generations.end()) {
        generations.emplace(entity.id, 1);
    } else {
        generation_iter->second++;
    }

    for (auto& [type, index] : entity_iter->second) {
        auto components_collection = components[type].get();
        Entity owner = components_collection->get_owner(components_collection->size() - 1);
        components_collection->remove(index);
        entities[owner][type] = index;
    }

    entities.erase(entity);

    return true;
}
