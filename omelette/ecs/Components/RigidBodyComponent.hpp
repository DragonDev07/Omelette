#ifndef OMELETTE_ECS_COMPONENTS_RIGIDBODYCOMPONENT_HPP
#define OMELETTE_ECS_COMPONENTS_RIGIDBODYCOMPONENT_HPP

#include <memory>

#include "../../utils/Vec3.hpp"
#include "../Component.hpp"
#include "ecs/Components/MeshComponent.hpp"

namespace omelette::ecs::components {
    class RigidBodyComponent: public omelette::ecs::Component {
      public:
        utils::Vec3 position; // Position of the rigid body
        utils::Vec3 velocity; // Velocity of the rigid body
        utils::Vec3 acceleration; // Acceleration of the rigid body
        float mass; // Mass of the rigid body
        MeshComponent* meshComponent; // Reference to associated mesh component

        // Parameterized constructor
        RigidBodyComponent(
            const utils::Vec3& position,
            const utils::Vec3& velocity,
            const utils::Vec3& acceleration,
            float mass,
            MeshComponent* meshComponent
        );

        // Update the rigid body's position and velocity
        void update(float deltaTime) override;

        // Clone function for copying components
        std::unique_ptr<Component> clone() const override;

        // Apply a force to the rigid body
        void applyForce(const utils::Vec3& force);
    };
}; // namespace omelette::ecs::components

#endif // OMELETTE_ECS_COMPONENTS_RIGIDBODYCOMPONENT_HPP
