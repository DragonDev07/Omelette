#pragma once
#include "Vec3.hpp"

class RigidBody {
    public:
        Vec3 position; // Position of the rigid body
        Vec3 velocity; // Velocity of the rigid body
        Vec3 acceleration; // Acceleration of the rigid body
        float mass; // Mass of the rigid body

        // Constructors
        RigidBody(); // Default constructor
        RigidBody(const Vec3& position, const Vec3& velocity, const Vec3& acceleration, float mass); // Parameterized constructor

        // Functions
        void applyForce(const Vec3& force); // Apply a force to the rigid body
        void update(float deltaTime); // Update the rigid body's position and velocity
};