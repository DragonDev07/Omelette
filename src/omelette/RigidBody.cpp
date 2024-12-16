#include "RigidBody.hpp"

/* RigidBody Default Constructor
    - Sets the rigid body's position, velocity, and acceleration to zero and mass to 1. */
RigidBody::RigidBody() : position(), velocity(), acceleration(), mass(1.0f) {}

/* RigidBody Constructor
    - Sets the rigid body's position, velocity, acceleration, and mass to the given values. */
RigidBody::RigidBody(const Vec3& position, const Vec3& velocity, const Vec3& acceleration, float mass) 
    : position(position), velocity(velocity), acceleration(acceleration), mass(mass) {}

/* Apply Force
    - Applies a force to the rigid body by adding the force divided by the mass to the acceleration. */
void RigidBody::applyForce(const Vec3& force) {
    acceleration += force / mass;
}

/* Update
    - Updates the rigid body's position and velocity based on the current acceleration and time step. */
void RigidBody::update(float deltaTime) {
    // Update velocity based on acceleration
    velocity += acceleration * deltaTime;

    // Update position based on velocity
    position += velocity * deltaTime;

    // Reset acceleration to zero
    acceleration = Vec3();
}