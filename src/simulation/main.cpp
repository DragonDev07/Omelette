#include <iostream>
#include "Vec3.hpp"
#include "RigidBody.hpp"
#include "PhysicsWorld.hpp"

int main() {
    PhysicsWorld world;
    auto body = std::make_unique<RigidBody>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
    world.addRigidBody(std::move(body));

    auto& bodyRef = world.getRigidBodies()[0];

    for (int i = 0; i < 1000; i++) {
        world.step(0.016f); // 1/60 = ~0.016 for 60fps
        std::cout << "Step " << i << " | " << "Position: (" << bodyRef->position.x << ", " << bodyRef->position.y << ", " << bodyRef->position.z << ")" << std::endl;
    }

    return 0;
}