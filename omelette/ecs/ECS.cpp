#include "ECS.hpp"

namespace omelette::ecs {
    /* Add Entity
    - Adds an entity to the ECS.
    - Parameters:
        - entity: The entity to add. */
    void ECS::addEntity(std::unique_ptr<omelette::ecs::Entity> entity) {
        entities.push_back(std::move(entity));
    }

    /* Add Component To Entity
    - Adds a component to an entity.
    - Parameters:
        - entity: The entity to add the component to.
        - component: The component to add. */
    void ECS::addComponentToEntity(
        omelette::ecs::Entity& entity,
        std::unique_ptr<omelette::ecs::Component> component
    ) {
        entityComponents[&entity].push_back(std::move(component));
    }

    /* Get Entities
    - Returns the list of entities in the ECS.
    - Returns: The list of entities. */
    const std::vector<std::unique_ptr<omelette::ecs::Entity>>&
    ECS::getEntities() const {
        return entities;
    }

    /* Get Components
    - Returns the list of components in the ECS.
    - Returns: The list of components. */
    const std::vector<std::unique_ptr<omelette::ecs::Component>>&
    ECS::getComponents() const {
        static std::vector<std::unique_ptr<omelette::ecs::Component>>
            allComponents;
        allComponents.clear();
        for (const auto& pair : entityComponents) {
            for (const auto& component : pair.second) {
                allComponents.push_back(component->clone());
            }
        }
        return allComponents;
    }

    /* Get Entities by Component
    - Returns a list of entities that have a specific component type.
    - Template Parameters:
        - T: The component type to search for.
    - Returns: The list of entities with the specified component type. */
    template<typename T>
    std::vector<omelette::ecs::Entity*> ECS::getEntitiesByComponent() const {
        std::vector<omelette::ecs::Entity*> entitiesWithComponent;
        for (const auto& pair : entityComponents) {
            for (const auto& component : pair.second) {
                if (std::is_same<T, std::decay_t<decltype(*component)>>::
                        value) {
                    entitiesWithComponent.push_back(pair.first);
                    break;
                }
            }
        }
        return entitiesWithComponent;
    }

    /* Get Components for Entity
    - Returns a list of components for a specific entity.
    - Parameters:
        - entity: The entity to get components for.
    - Returns: The list of components for the entity. */
    const std::vector<std::unique_ptr<omelette::ecs::Component>>&
    ECS::getComponentsForEntity(const omelette::ecs::Entity& entity) const {
        static std::vector<std::unique_ptr<omelette::ecs::Component>> empty;
        auto it =
            entityComponents.find(const_cast<omelette::ecs::Entity*>(&entity));
        if (it != entityComponents.end()) {
            return it->second;
        }
        return empty;
    }
}; // namespace omelette::ecs
