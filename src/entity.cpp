#include "globular/entity.hpp"

bool Entity::operator==(const Entity& other) const {
    return id == other.id && generation == other.generation;
}
