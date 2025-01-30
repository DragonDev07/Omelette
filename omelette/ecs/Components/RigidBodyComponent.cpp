#include "RigidBodyComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "ecs/Components/MeshComponent.hpp"

namespace omelette::ecs::components {
    /* RigidBodyComponent Constructor
    - Sets the rigid body's position, velocity, acceleration, and mass to the given values.
    - Initializes the shape data with the given vertices and indices. */
    RigidBodyComponent::RigidBodyComponent(
        const utils::Vec3& position,
        const utils::Vec3& velocity,
        const utils::Vec3& acceleration,
        float mass,
        MeshComponent* meshComponent
    ) :
        position(position),
        velocity(velocity),
        acceleration(acceleration),
        mass(mass),
        meshComponent(meshComponent) {}

    /* Update
        - Updates the rigid body's position and velocity based on the current acceleration and time step.
        - Parameters:
            - deltaTime: The time step to update the rigid body by. */
    void RigidBodyComponent::update(float deltaTime) {
        // Update velocity based on acceleration
        velocity += acceleration * deltaTime;

        // Update position based on velocity
        position += velocity * deltaTime;

        // Create transformation matrix
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(
            transform,
            glm::vec3(position.x, position.y, position.z)
        );

        // Update mesh component with new transform
        if (meshComponent) {
            meshComponent->transform(transform);
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

    /* Apply Force
    - Applies a force to the rigid body by adding the force divided by the mass to the acceleration.
    - Parameters:
        - force: The force to apply to the rigid body. */
    void RigidBodyComponent::applyForce(const utils::Vec3& force) {
        acceleration += force / mass;
    }
}; // namespace omelette::ecs::components
