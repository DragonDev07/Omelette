#include "PhysicsWorld.hpp"

/* PhysicsWorld Default Constructor
    - Initializes the list of rigid bodies. */
PhysicsWorld::PhysicsWorld() : rigidBodies() {}

/* Add Rigid Body to Physics World
    - Adds a rigid body to the world. */
void PhysicsWorld::addRigidBody(std::unique_ptr<RigidBody> rigidBody) {
    rigidBodies.push_back(std::move(rigidBody));
}

/* Get Rigid Bodies
    - Returns the list of rigid bodies in the world. */
const std::vector<std::unique_ptr<RigidBody>>& PhysicsWorld::getRigidBodies() const {
    return rigidBodies;
}

/* Step Physics Simulation
    - Advances the simulation by a given time interval. */
void PhysicsWorld::step(float deltaTime) {
    // Apply gravity to all rigid bodies.
    Vec3 gravity(0.0f, -9.81f, 0.0f);
    for (auto& body : rigidBodies) {
        body->applyForce(gravity * body->mass);
    }

    // Update all rigid bodies.
    for (auto& body : rigidBodies) {
        body->update(deltaTime);
    }
}  