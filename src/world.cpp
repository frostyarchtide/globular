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
    entities.emplace(id, generation);

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

    entities.erase(entity);

    return true;
}

bool World::contains_entity(Entity entity) {
    return entities.find(entity) != entities.end();
}
