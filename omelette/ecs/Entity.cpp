#include "Entity.hpp"

/* Entity Constructor
    - Initializes the entity with a unique identifier.
    - Parameters:
        - id: The unique identifier for the entity. */
Entity::Entity(std::uint32_t id) : id(id) {}

/* Get ID
    - Returns the unique identifier of the entity.
    - Returns: The unique identifier. */
std::uint32_t Entity::getId() const {
    return id;
}