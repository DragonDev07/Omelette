#pragma once

class Vec3 {
    public:
        float x, y, z; // The x, y, and z coordinates of the vector

        // Constructors
        Vec3(); // Default constructor
        Vec3(float x, float y, float z); // Parameterized constructor

        // Operator overloads
        Vec3 operator+(const Vec3& other) const; // Addition of two vectors
        Vec3 operator-(const Vec3& other) const; // Subtraction of two vectors
        Vec3 operator*(float scalar) const; // Multiplication of vector by a scalar
        Vec3 operator/(float scalar) const; // Division of vector by a scalar
        Vec3 operator+=(const Vec3& other); // Compound addition of two vectors
        Vec3 operator-=(const Vec3& other); // Compound subtraction of two vectors

        // Vector operations
        float dot(const Vec3& other) const; // Dot product of two vectors
        Vec3 cross(const Vec3& other) const; // Cross product of two vectors
        float magnitude() const; // Magnitude (length) of the vector
        Vec3 normalize() const; // Normalized vector (unit vector)
        static Vec3 lerp(const Vec3& start, const Vec3& end, float t); // Linear interpolation
};
