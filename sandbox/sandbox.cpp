#include <ecs/Components/MeshComponent.hpp>
#include <ecs/Components/RigidBodyComponent.hpp>
#include <ecs/ECS.hpp>
#include <ecs/Entity.hpp>
#include <iomanip>
#include <iostream>
#include <utils/Shapes.hpp>
#include <utils/Vec3.hpp>

// Helper function to print vertex positions
void printVertexPositions(const std::vector<omelette::utils::Vec3>& vertices) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Cube vertices positions: [";
    for (size_t i = 0; i < vertices.size(); ++i) {
        const auto& v = vertices[i];
        std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        if (i < vertices.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n\n";
}

int main(int argc, char* argv[]) {
    // Create ECS instance
    omelette::ecs::ECS ecs;

    // Create entity
    auto entity = std::make_unique<omelette::ecs::Entity>();
    auto entityPtr = entity.get();

    // Create cube shape
    auto [vertices, indices] = omelette::utils::Shapes::createCube();

    // Create Mesh component
    auto meshComponent =
        std::make_unique<omelette::ecs::components::MeshComponent>(
            vertices,
            indices
        );
    auto meshComponentPtr = meshComponent.get();

    // Create RigidBody component
    auto rigidBody =
        std::make_unique<omelette::ecs::components::RigidBodyComponent>(
            omelette::utils::Vec3(0, 0, 0), // position
            omelette::utils::Vec3(0, 0, 0), // velocity
            omelette::utils::Vec3(0, 0, 0), // acceleration
            1.0f, // mass
            meshComponentPtr // reference to mesh component
        );

    // Add entity to ECS
    ecs.addEntity(std::move(entity));

    // Add components to entity
    ecs.addComponentToEntity(*entityPtr, std::move(meshComponent));
    ecs.addComponentToEntity(*entityPtr, std::move(rigidBody));

    // Simulation loop
    float deltaTime = 0.016f; // 60 FPS
    float simulationTime = 0.0f;
    float maxSimulationTime = 5.0f; // Run for 5 seconds

    // Apply a force in 3D space
    omelette::utils::Vec3 force(
        1.0f, // x
        0.0f, // y
        0.0f // z
    ); // Modified to show 3D movement

    std::cout << "Starting simulation with force: (" << force.x << ", "
              << force.y << ", " << force.z << ")\n\n";

    // Apply force
    rb->applyForce(force);

    while (simulationTime < maxSimulationTime) {
        // Get components for the entity
        const auto& components = ecs.getComponentsForEntity(*entityPtr);

        // Find and update RigidBody component
        for (const auto& component : components) {
            if (auto* rb = dynamic_cast<
                    omelette::ecs::components::RigidBodyComponent*>(
                    component.get()
                )) {
                if (simulationTime == 0) {
                    rb->applyForce(force);
                }

                // Update physics
                rb->update(deltaTime);

                // Output center position and vertices
                std::cout << "Time: " << std::fixed << std::setprecision(2)
                          << simulationTime << "s\n";
                std::cout << "Center Position: (" << rb->position.x << ", "
                          << rb->position.y << ", " << rb->position.z << ")\n";

                // Print all vertex positions from the mesh component
                if (rb->meshComponent) {
                    printVertexPositions(rb->meshComponent->getVertices());
                }
            }
        }

        // Update simulation time
        simulationTime += deltaTime;
    }

    return 0;
}
