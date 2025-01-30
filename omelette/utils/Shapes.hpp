#ifndef OMELLETE_UTILS_SHAPES_HPP
#define OMELLETE_UTILS_SHAPES_HPP

#include <cstdint>
#include <tuple>
#include <vector>

#include "Vec3.hpp"

namespace omelette::utils::Shapes {
    // Cube / Rectangular Prism
    std::tuple<std::vector<omelette::utils::Vec3>, std::vector<uintptr_t>>
    createCube(float width = 1.0f, float height = 1.0f, float depth = 1.0f);

    // Plane
    std::tuple<std::vector<omelette::utils::Vec3>, std::vector<uintptr_t>>
    createPlane(float width = 1.0f, float depth = 1.0f);

    // Sphere (UV)
    std::tuple<std::vector<omelette::utils::Vec3>, std::vector<uintptr_t>>
    createUVSphere(
        float radius = 1.0f,
        unsigned int segments = 16,
        unsigned int rings = 16
    );

    // Sphere (Icosphere)
    std::tuple<std::vector<omelette::utils::Vec3>, std::vector<uintptr_t>>
    createIcosphere(float radius = 1.0f, unsigned int subdivisions = 1);

    // Cylinder
    std::tuple<std::vector<omelette::utils::Vec3>, std::vector<uintptr_t>>
    createCylinder(
        float radius = 1.0f,
        float height = 1.0f,
        unsigned int segments = 16
    );

} // namespace omelette::utils::Shapes

#endif
