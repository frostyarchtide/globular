#pragma once

#include <cstdint>
#include <functional>

struct Entity {
    uint32_t id;
    uint32_t generation;

    Entity(uint32_t id, uint32_t generation)
        : id(id),
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
