#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "Entity.hpp"
#include "Component.hpp"

class ECS {
    private:
        std::vector<std::unique_ptr<Entity>> entities; // List of entities in the ECS
        std::unordered_map<Entity*, std::vector<std::unique_ptr<Component>>> entityComponents; // Map of entities to their components

    public:
        // Functions
        void addEntity(std::unique_ptr<Entity> entity); // Add an entity to the ECS
        void addComponentToEntity(Entity& entity, std::unique_ptr<Component> component); // Add a component to an entity
        const std::vector<std::unique_ptr<Entity>>& getEntities() const; // Get the list of entities
        const std::vector<std::unique_ptr<Component>>& getComponents() const; // Get the list of components
        const std::vector<std::unique_ptr<Component>>& getComponentsForEntity(const Entity& entity) const; // Get components for a specific entity

        template <typename T>
        std::vector<Entity*> getEntitiesByComponent() const; // Get entities with a specific component type
};