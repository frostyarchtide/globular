#pragma once

#include <cstdint>
#include <functional>

class World;

struct Entity {
    World* world;
    uint32_t id;
    uint32_t generation;

    Entity(World* world, uint32_t id, uint32_t generation)
        : world(world),
        id(id),
        generation(generation)
    {}

    bool operator==(const Entity& other) const;
};

namespace std {
    template <>
    struct hash<Entity> {
        size_t operator()(const Entity& entity) const {
            return std::hash<uint32_t>()(entity.id) ^ std::hash<uint32_t>()(entity.generation << 1);
        }
    };
};
