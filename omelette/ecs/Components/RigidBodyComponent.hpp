#ifndef OMELETTE_ECS_COMPONENTS_RIGIDBODYCOMPONENT_HPP
#define OMELETTE_ECS_COMPONENTS_RIGIDBODYCOMPONENT_HPP

#include <cstdint>
#include <memory>
#include <vector>

#include "../../utils/Vec3.hpp"
#include "../Component.hpp"

namespace omelette::ecs::components {
    class RigidBodyComponent: public omelette::ecs::Component {
      public:
        Vec3 position; // Position of the rigid body
        Vec3 velocity; // Velocity of the rigid body
        Vec3 acceleration; // Acceleration of the rigid body
        float mass; // Mass of the rigid body
        std::vector<Vec3> vertices; // Vertex buffer object (VBO)
        std::vector<uintptr_t> indices; // Element buffer object (EBO)

        // Parameterized constructor
        RigidBodyComponent(
            const Vec3& position,
            const Vec3& velocity,
            const Vec3& acceleration,
            float mass,
            const std::vector<Vec3>& vertices,
            const std::vector<uintptr_t>& indices
        );

        // Apply a force to the rigid body
        void applyForce(const Vec3& force);

        // Update the rigid body's position and velocity
        void update(float deltaTime) override;

        // Clone function for copying components
        std::unique_ptr<Component> clone() const override;

        // Getters for shape data
        const std::vector<Vec3>& getVertices() const;
        const std::vector<uintptr_t>& getIndices() const;
    };
}; // namespace omelette::ecs::components

#endif // OMELETTE_ECS_COMPONENTS_RIGIDBODYCOMPONENT_HPP
