#pragma once
#include <vector>
#include <memory>
#include "RigidBody.hpp"

class PhysicsWorld {
    private:
        std::vector<std::unique_ptr<RigidBody>> rigidBodies; // List of rigid bodies in the world

    public:
        // Constructor
        PhysicsWorld();

        // Functions
        void addRigidBody(std::unique_ptr<RigidBody> rigidBody); // Add a rigid body to the world
        void step(float deltaTime); // Step the simulation forward by a given time interval
        const std::vector<std::unique_ptr<RigidBody>>& getRigidBodies() const; // Get the list of rigid bodies
};