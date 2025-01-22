#include <chrono>
#include <ecs/Components/RigidBodyComponent.hpp>
#include <ecs/ECS.hpp>
#include <ecs/Entity.hpp>
#include <iomanip>
#include <iostream>
#include <thread>
#include <utils/Vec3.hpp>

// Helper function to create a cube shape
std::pair<std::vector<omelette::utils::Vec3>, std::vector<uintptr_t>>
createCube(float size) {
    float halfSize = size / 2.0f;

    // Create 8 vertices for cube
    std::vector<omelette::utils::Vec3> vertices = {
        // Front face
        omelette::utils::Vec3(-halfSize, -halfSize, halfSize), // 0
        omelette::utils::Vec3(halfSize, -halfSize, halfSize), // 1
        omelette::utils::Vec3(halfSize, halfSize, halfSize), // 2
        omelette::utils::Vec3(-halfSize, halfSize, halfSize), // 3
        // Back face
        omelette::utils::Vec3(-halfSize, -halfSize, -halfSize), // 4
        omelette::utils::Vec3(halfSize, -halfSize, -halfSize), // 5
        omelette::utils::Vec3(halfSize, halfSize, -halfSize), // 6
        omelette::utils::Vec3(-halfSize, halfSize, -halfSize) // 7
    };

    // Create indices for the triangles (12 triangles, 36 indices)
    std::vector<uintptr_t> indices = {// Front face
                                      0,
                                      1,
                                      2,
                                      2,
                                      3,
                                      0,
                                      // Right face
                                      1,
                                      5,
                                      6,
                                      6,
                                      2,
                                      1,
                                      // Back face
                                      5,
                                      4,
                                      7,
                                      7,
                                      6,
                                      5,
                                      // Left face
                                      4,
                                      0,
                                      3,
                                      3,
                                      7,
                                      4,
                                      // Top face
                                      3,
                                      2,
                                      6,
                                      6,
                                      7,
                                      3,
                                      // Bottom face
                                      4,
                                      5,
                                      1,
                                      1,
                                      0,
                                      4
    };

    return {vertices, indices};
}

// Helper function to print vertex positions
void printVertexPositions(const std::vector<omelette::utils::Vec3>& vertices) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Cube vertices positions:\n";
    for (size_t i = 0; i < vertices.size(); ++i) {
        const auto& v = vertices[i];
        std::cout << "V" << i << ": (" << std::setw(8) << v.x << ", "
                  << std::setw(8) << v.y << ", " << std::setw(8) << v.z
                  << ")\n";
    }
    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    // Create ECS instance
    omelette::ecs::ECS ecs;

    // Create entity
    auto entity = std::make_unique<omelette::ecs::Entity>();
    auto entityPtr = entity.get();

    // Create cube shape
    auto [vertices, indices] = createCube(2.0f); // Create a 2x2x2 cube

    // Create RigidBody component
    auto rigidBody =
        std::make_unique<omelette::ecs::components::RigidBodyComponent>(
            omelette::utils::Vec3(0, 0, 0), // position
            omelette::utils::Vec3(0, 0, 0), // velocity
            omelette::utils::Vec3(0, 0, 0), // acceleration
            1.0f, // mass
            vertices, // vertices
            indices // indices
        );

    // Add entity to ECS
    ecs.addEntity(std::move(entity));

    // Add RigidBody component to entity
    ecs.addComponentToEntity(*entityPtr, std::move(rigidBody));

    // Simulation loop
    float deltaTime = 0.016f; // 60 FPS
    float simulationTime = 0.0f;
    float maxSimulationTime = 5.0f; // Run for 5 seconds

    // Apply a force in 3D space
    omelette::utils::Vec3 force(10.0f, 0.0f, 0.0f);

    std::cout << "Starting simulation with force: (" << force.x << ", "
              << force.y << ", " << force.z << ")\n\n";

    while (simulationTime < maxSimulationTime) {
        // Get components for the entity
        const auto& components = ecs.getComponentsForEntity(*entityPtr);

        // Find and update RigidBody component
        for (const auto& component : components) {
            if (auto* rb = dynamic_cast<
                    omelette::ecs::components::RigidBodyComponent*>(
                    component.get()
                )) {
                // Apply force
                rb->applyForce(force);

                // Update physics
                rb->update(deltaTime);

                // Output center position and vertices
                std::cout << "Time: " << std::fixed << std::setprecision(2)
                          << simulationTime << "s\n";
                std::cout << "Center Position: (" << rb->position.x << ", "
                          << rb->position.y << ", " << rb->position.z << ")\n";

                // Print all vertex positions
                printVertexPositions(rb->getVertices());
            }
        }

        // Update simulation time
        simulationTime += deltaTime;
    }

    return 0;
}
