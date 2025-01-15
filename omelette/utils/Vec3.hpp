#ifndef OMELETTE_UTILS_VEC3_HPP
#define OMELETTE_UTILS_VEC3_HPP

namespace omelette::utils {
    class Vec3 {
      public:
        float x, y, z; // The x, y, and z coordinates of the vector

        // Default constructor
        Vec3();

        // Parameterized constructor
        Vec3(float x, float y, float z);

        // Addition of two vectors
        Vec3 operator+(const Vec3& other) const;

        // Subtraction of two vectors
        Vec3 operator-(const Vec3& other) const;

        // Multiplication of vector by a scalar
        Vec3 operator*(float scalar) const;

        // Division of vector by a scalar
        Vec3 operator/(float scalar) const;

        // Compound addition of two vectors
        Vec3 operator+=(const Vec3& other);

        // Compound subtraction of two vectors
        Vec3 operator-=(const Vec3& other);

        // Dot product of two vectors
        float dot(const Vec3& other) const;

        // Cross product of two vectors
        Vec3 cross(const Vec3& other) const;

        // Magnitude (length) of the vector
        float magnitude() const;

        // Normalized vector (unit vector)
        Vec3 normalize() const;

        // Linear interpolation
        static Vec3 lerp(const Vec3& start, const Vec3& end, float t);
    };
}; // namespace omelette::utils

#endif // OMELETTE_UTILS_VEC3_HPP
