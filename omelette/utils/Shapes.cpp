#include "Shapes.hpp"

#include <cmath>
#include <tuple>
#include <vector>

namespace omelette::utils::Shapes {
    std::tuple<std::vector<Vec3>, std::vector<uintptr_t>>
    createCube(float width, float height, float depth) {
        float w = width * 0.5f;
        float h = height * 0.5f;
        float d = depth * 0.5f;

        std::vector<Vec3> vertices = {
            // Front face
            Vec3(-w, -h, d), // 0
            Vec3(w, -h, d), // 1
            Vec3(w, h, d), // 2
            Vec3(-w, h, d), // 3

            // Back face
            Vec3(-w, -h, -d), // 4
            Vec3(w, -h, -d), // 5
            Vec3(w, h, -d), // 6
            Vec3(-w, h, -d) // 7
        };

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

    std::tuple<std::vector<Vec3>, std::vector<uintptr_t>>
    createPlane(float width, float depth) {
        float w = width * 0.5f;
        float d = depth * 0.5f;

        std::vector<Vec3> vertices = {
            Vec3(-w, 0, -d), // 0
            Vec3(w, 0, -d), // 1
            Vec3(w, 0, d), // 2
            Vec3(-w, 0, d) // 3
        };

        std::vector<uintptr_t> indices = {
            0,
            1,
            2, // First triangle
            2,
            3,
            0 // Second triangle
        };

        return {vertices, indices};
    }

    std::tuple<std::vector<Vec3>, std::vector<uintptr_t>>
    createUVSphere(float radius, unsigned int segments, unsigned int rings) {
        std::vector<Vec3> vertices;
        std::vector<uintptr_t> indices;

        // Generate vertices
        for (unsigned int ring = 0; ring <= rings; ring++) {
            float phi = M_PI * float(ring) / float(rings);
            for (unsigned int segment = 0; segment <= segments; segment++) {
                float theta = 2.0f * M_PI * float(segment) / float(segments);

                float x = radius * sin(phi) * cos(theta);
                float y = radius * cos(phi);
                float z = radius * sin(phi) * sin(theta);

                vertices.push_back(Vec3(x, y, z));
            }
        }

        // Generate indices
        for (unsigned int ring = 0; ring < rings; ring++) {
            for (unsigned int segment = 0; segment < segments; segment++) {
                uintptr_t current = ring * (segments + 1) + segment;
                uintptr_t next = current + segments + 1;

                indices.push_back(current);
                indices.push_back(next);
                indices.push_back(current + 1);

                indices.push_back(current + 1);
                indices.push_back(next);
                indices.push_back(next + 1);
            }
        }

        return {vertices, indices};
    }

    std::tuple<std::vector<Vec3>, std::vector<uintptr_t>>
    createIcosphere(float radius, unsigned int subdivisions) {
        // Start with icosahedron vertices
        const float t = (1.0f + std::sqrt(5.0f)) / 2.0f;

        std::vector<Vec3> vertices = {
            Vec3(-1, t, 0).normalize() * radius,
            Vec3(1, t, 0).normalize() * radius,
            Vec3(-1, -t, 0).normalize() * radius,
            Vec3(1, -t, 0).normalize() * radius,

            Vec3(0, -1, t).normalize() * radius,
            Vec3(0, 1, t).normalize() * radius,
            Vec3(0, -1, -t).normalize() * radius,
            Vec3(0, 1, -t).normalize() * radius,

            Vec3(t, 0, -1).normalize() * radius,
            Vec3(t, 0, 1).normalize() * radius,
            Vec3(-t, 0, -1).normalize() * radius,
            Vec3(-t, 0, 1).normalize() * radius
        };

        // Initial icosahedron faces
        std::vector<uintptr_t> indices = {
            0, 11, 5,  0, 5,  1, 0, 1, 7, 0, 7,  10, 0, 10, 11, 1, 5, 9, 5, 11,
            4, 11, 10, 2, 10, 7, 6, 7, 1, 8, 3,  9,  4, 3,  4,  2, 3, 2, 6, 3,
            6, 8,  3,  8, 9,  4, 9, 5, 2, 4, 11, 6,  2, 10, 8,  6, 7, 9, 8, 1
        };

        // Helper function to get middle point of two vertices
        auto getMiddlePoint =
            [&vertices, radius](uintptr_t p1, uintptr_t p2) -> uintptr_t {
            Vec3 middle = (vertices[p1] + vertices[p2]) * 0.5f;
            middle = middle.normalize() * radius;

            // Check if we already have this vertex
            for (size_t i = 0; i < vertices.size(); i++) {
                if ((vertices[i] - middle).magnitude() < 0.00001f) {
                    return i;
                }
            }

            vertices.push_back(middle);
            return vertices.size() - 1;
        };

        // Perform subdivisions
        for (unsigned int i = 0; i < subdivisions; i++) {
            std::vector<uintptr_t> newIndices;

            // Subdivide each triangle into 4 triangles
            for (size_t j = 0; j < indices.size(); j += 3) {
                uintptr_t a = indices[j];
                uintptr_t b = indices[j + 1];
                uintptr_t c = indices[j + 2];

                // Get middle points
                uintptr_t ab = getMiddlePoint(a, b);
                uintptr_t bc = getMiddlePoint(b, c);
                uintptr_t ca = getMiddlePoint(c, a);

                // Add four triangles
                newIndices.push_back(a);
                newIndices.push_back(ab);
                newIndices.push_back(ca);

                newIndices.push_back(b);
                newIndices.push_back(bc);
                newIndices.push_back(ab);

                newIndices.push_back(c);
                newIndices.push_back(ca);
                newIndices.push_back(bc);

                newIndices.push_back(ab);
                newIndices.push_back(bc);
                newIndices.push_back(ca);
            }

            indices = newIndices;
        }

        return {vertices, indices};
    }

    std::tuple<std::vector<Vec3>, std::vector<uintptr_t>>
    createCylinder(float radius, float height, unsigned int segments) {
        std::vector<Vec3> vertices;
        std::vector<uintptr_t> indices;

        float halfHeight = height * 0.5f;

        // Center vertices
        vertices.push_back(Vec3(0, -halfHeight, 0)); // Bottom center
        vertices.push_back(Vec3(0, halfHeight, 0)); // Top center

        // Generate vertices for top and bottom circles
        for (unsigned int i = 0; i <= segments; i++) {
            float theta = 2.0f * M_PI * float(i) / float(segments);
            float x = radius * cos(theta);
            float z = radius * sin(theta);

            vertices.push_back(Vec3(x, -halfHeight, z)); // Bottom ring
            vertices.push_back(Vec3(x, halfHeight, z)); // Top ring
        }

        // Generate indices for the sides
        for (unsigned int i = 0; i < segments; i++) {
            uintptr_t bottomFirst = 2 + (i * 2);
            uintptr_t bottomSecond = bottomFirst + 2;
            uintptr_t topFirst = bottomFirst + 1;
            uintptr_t topSecond = bottomSecond + 1;

            // Side faces
            indices.push_back(bottomFirst);
            indices.push_back(topFirst);
            indices.push_back(bottomSecond);

            indices.push_back(bottomSecond);
            indices.push_back(topFirst);
            indices.push_back(topSecond);

            // Bottom cap
            indices.push_back(0);
            indices.push_back(bottomFirst);
            indices.push_back(bottomSecond);

            // Top cap
            indices.push_back(1);
            indices.push_back(topSecond);
            indices.push_back(topFirst);
        }

        return {vertices, indices};
    }

} // namespace omelette::utils::Shapes
