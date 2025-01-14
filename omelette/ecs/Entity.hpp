#pragma once
#include <cstdint>

class Entity {
    private:
        std::uint32_t id; // Unique identifier for the entity

    public:
        // Constructor
        Entity(std::uint32_t id);

        // Get the unique identifier of the entity
        std::uint32_t getId() const;
};