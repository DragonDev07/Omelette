#include "RigidBodyComponent.hpp"

#include <cstdint>

namespace omelette::ecs::components {
    /* RigidBodyComponent Constructor
    - Sets the rigid body's position, velocity, acceleration, and mass to the given values.
    - Initializes the shape data with the given vertices and indices. */
    RigidBodyComponent::RigidBodyComponent(
        const utils::Vec3& position,
        const utils::Vec3& velocity,
        const utils::Vec3& acceleration,
        float mass,
        const std::vector<utils::Vec3>& vertices,
        const std::vector<uintptr_t>& indices
    ) :
        position(position),
        velocity(velocity),
        acceleration(acceleration),
        mass(mass),
        vertices(vertices),
        indices(indices) {}

    /* Apply Force
    - Applies a force to the rigid body by adding the force divided by the mass to the acceleration.
    - Parameters:
        - force: The force to apply to the rigid body. */
    void RigidBodyComponent::applyForce(const utils::Vec3& force) {
        acceleration += force / mass;
    }

    /* Update
    - Updates the rigid body's position and velocity based on the current acceleration and time step.
    - Parameters:
        - deltaTime: The time step to update the rigid body by. */
    void RigidBodyComponent::update(float deltaTime) {
        // Update velocity based on acceleration
        velocity += acceleration * deltaTime;

        // Update position based on velocity
        position += velocity * deltaTime;

        // Update vertex positions based on rigid body position
        for (auto& vertex : vertices) {
            vertex += velocity * deltaTime;
        }

        // Reset acceleration to zero
        acceleration = utils::Vec3();
    }

    /* Clone
    - Creates a copy of the rigid body component.
    - Returns: A unique pointer to the copied component. */
    std::unique_ptr<omelette::ecs::Component>
    RigidBodyComponent::clone() const {
        return std::make_unique<RigidBodyComponent>(*this);
    }

    /* Get Vertices
    - Returns the vertices of the shape.
    - Returns: The vertices of the shape. */
    const std::vector<utils::Vec3>& RigidBodyComponent::getVertices() const {
        return vertices;
    }

    /* Get Indices
    - Returns the indices of the shape.
    - Returns: The indices of the shape. */
    const std::vector<uintptr_t>& RigidBodyComponent::getIndices() const {
        return indices;
    }
}; // namespace omelette::ecs::components
