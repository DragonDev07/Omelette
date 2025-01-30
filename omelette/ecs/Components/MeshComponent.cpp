#include "MeshComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <memory>

namespace omelette::ecs::components {
    MeshComponent::MeshComponent(
        std::vector<utils::Vec3>& vertices,
        const std::vector<uintptr_t>& indices
    ) :
        vertices(vertices),
        indices(indices) {}

    /* Update
        - Updates the mesh component's state based on elapsed time.
        - Parameters:
            - deltaTime: Time elapsed since last update */
    void MeshComponent::update(float deltaTime) {
        // No default update behavior
    }

    /* Transform
        - Applies a transformation matrix to all vertices in the mesh.
        - Parameters:
            - transformMatrix: 4x4 matrix defining the transformation to apply */
    void MeshComponent::transform(const glm::mat4& transformMatrix) {
        for (auto& vertex : vertices) {
            // Convert Vec3 to glm::vec4 for transformation (w = 1.0 for position)
            glm::vec4 v(vertex.x, vertex.y, vertex.z, 1.0f);

            // Apply transformation
            v = transformMatrix * v;

            // Convert back to Vec3
            vertex.x = v.x;
            vertex.y = v.y;
            vertex.z = v.z;
        }
    }

    /* Clone
        - Creates a deep copy of this mesh component.
        - Returns: A unique pointer to the newly created copy */
    std::unique_ptr<Component> MeshComponent::clone() const {
        return std::make_unique<MeshComponent>(*this);
    }

    /* Get Vertices
        - Retrieves the mesh's vertex data.
        - Returns: Constant reference to the vector of vertices */
    const std::vector<utils::Vec3>& MeshComponent::getVertices() const {
        return vertices;
    }

    /* Get Indices
        - Retrieves the mesh's index data.
        - Returns: Constant reference to the vector of indices */
    const std::vector<uintptr_t>& MeshComponent::getIndices() const {
        return indices;
    }
} // namespace omelette::ecs::components
