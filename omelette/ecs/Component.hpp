#ifndef OMELETTE_ECS_COMPONENT_HPP
#define OMELETTE_ECS_COMPONENT_HPP

#include <memory>

namespace omelette::ecs {
    class Component {
      public:
        // Virtual destructor for polymorphic deletion
        virtual ~Component() = default;

        // Clone function for copying components
        virtual std::unique_ptr<Component> clone() const = 0;

        // Update function for updating component state
        virtual void update(float deltaTime) = 0;
    };
}; // namespace omelette::ecs

#endif // OMELETTE_ECS_COMPONENT_HPP
