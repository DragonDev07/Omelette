#pragma once
#include "../Component.hpp"
#include "../../utils/Vec3.hpp"
#include <cstdint>
#include <vector>
#include <memory>

class RigidBodyComponent : public Component {
    public:
        Vec3 position; // Position of the rigid body
        Vec3 velocity; // Velocity of the rigid body
        Vec3 acceleration; // Acceleration of the rigid body
        float mass; // Mass of the rigid body

        // Shape data
        std::vector<Vec3> vertices; // Vertex buffer object (VBO)
        std::vector<uintptr_t> indices; // Element buffer object (EBO)

        // Constructors
        RigidBodyComponent(); // Default constructor
        RigidBodyComponent(const Vec3& position, const Vec3& velocity, const Vec3& acceleration, float mass, const std::vector<Vec3>& vertices, const std::vector<uintptr_t>& indices); // Parameterized constructor

        // Destructor
        ~RigidBodyComponent() override = default;

        // Functions
        void applyForce(const Vec3& force); // Apply a force to the rigid body
        void update(float deltaTime) override; // Update the rigid body's position and velocity

        // Clone function for copying components
        std::unique_ptr<Component> clone() const override;

        // Getters for shape data
        const std::vector<Vec3>& getVertices() const;
        const std::vector<uintptr_t>& getIndices() const;
};
