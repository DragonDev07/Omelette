#ifndef OMELETTE_ECS_COMPONENTS_MESHCOMPONENT_HPP
#define OMELETTE_ECS_COMPONENTS_MESHCOMPONENT_HPP

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "../../utils/Vec3.hpp"
#include "../Component.hpp"

namespace omelette::ecs::components {
    class MeshComponent: public omelette::ecs::Component {
      public:
        std::vector<utils::Vec3>& vertices; // Vertex buffer object (VBO)
        const std::vector<uintptr_t>& indices; // Element buffer object (EBO)

        MeshComponent(
            std::vector<utils::Vec3>& vertices,
            const std::vector<uintptr_t>& indices
        );

        // Update the mesh's vertices
        void update(float deltaTime) override;
        void transform(const glm::mat4& transformMatrix);

        // Clone function for copying components
        std::unique_ptr<Component> clone() const override;

        // Getters for shape data
        const std::vector<utils::Vec3>& getVertices() const;
        const std::vector<uintptr_t>& getIndices() const;
    };
} // namespace omelette::ecs::components

#endif // OMELETTE_ECS_COMPONENTS_MESHCOMPONENT_HPP
