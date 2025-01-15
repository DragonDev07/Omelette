#ifndef OMELETTE_ECS_ECS_HPP
#define OMELETTE_ECS_ECS_HPP

#include <memory>
#include <unordered_map>
#include <vector>

#include "Component.hpp"
#include "Entity.hpp"

namespace omelette::ecs {
    class ECS {
      private:
        // List of entities
        std::vector<std::unique_ptr<omelette::ecs::Entity>> entities;

        // Map of entities to their components
        std::unordered_map<
            omelette::ecs::Entity*,
            std::vector<std::unique_ptr<omelette::ecs::Component>>>
            entityComponents;

      public:
        // Add an entity to the ECS
        void addEntity(std::unique_ptr<omelette::ecs::Entity> entity);

        // Add a component to an entity.
        void addComponentToEntity(
            omelette::ecs::Entity& entity,
            std::unique_ptr<omelette::ecs::Component> component
        );

        // Get the list of entities
        const std::vector<std::unique_ptr<omelette::ecs::Entity>>&
        getEntities() const;

        // Get the list of components
        const std::vector<std::unique_ptr<omelette::ecs::Component>>&
        getComponents() const;

        // Get components for a specific entity
        const std::vector<std::unique_ptr<omelette::ecs::Component>>&
        getComponentsForEntity(const omelette::ecs::Entity& entity) const;

        // Get entities with a specific component type
        template<typename T>
        std::vector<omelette::ecs::Entity*> getEntitiesByComponent() const;
    };
}; // namespace omelette::ecs

#endif // OMELETTE_ECS_ECS_HPP
