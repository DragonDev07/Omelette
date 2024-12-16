#include "Vec3.hpp"
#include <cmath>

/* Vec3 Default Constructor
    - Sets the Vector's x, y, and z components to 0. */
Vec3::Vec3() : x(0), y(0), z(0) {}

/* Vec3 Constructor
    - Sets the Vector's x, y, and z components to the given values. */
Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

/* Vec3 Addition Operator Overload
    - Adds the x, y, and z components of the two vectors and returns the result. */
Vec3 Vec3::operator+(const Vec3& other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

/* Vec3 Subtraction Operator Overload
    - Subtracts the x, y, and z components of the two vectors and returns the result. */
Vec3 Vec3::operator-(const Vec3& other) const {
    return Vec3(x - other.x, y - other.y, z - other.z);
}

/* Vec3 Scalar Multiplication Operator Overload
    - Multiplies the x, y, and z components of the vector by the given scalar and returns the result. */
Vec3 Vec3::operator*(float scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

/* Vec3 Scalar Division Operator Overload
    - Divides the x, y, and z components of the vector by the given scalar and returns the result. */
Vec3 Vec3::operator/(float scalar) const {
    return Vec3(x / scalar, y / scalar, z / scalar);
}

/* Vec3 Compound Addition Operator Overload
    - Adds the x, y, and z components of the two vectors and assigns the result to the vector. */
Vec3 Vec3::operator+=(const Vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

/* Vec3 Dot Product
    - Returns the dot product of the vector with another vector. */
float Vec3::dot(const Vec3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

/* Vec3 Cross Product
    - Returns the cross product of the vector with another vector. */
Vec3 Vec3::cross(const Vec3& other) const {
    return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

/* Vec3 Magnitude
    - Returns the magnitude (length) of the vector. */
float Vec3::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

/* Vec3 Normalization
    - Returns the normalized vector (unit vector) of the vector. */
Vec3 Vec3::normalize() const {
    float mag = magnitude();
    return Vec3(x / mag, y / mag, z / mag);
}

/* Vec3 Lerp
    - Linearly interpolates between two vectors by the given amount. */
Vec3 Vec3::lerp(const Vec3& start, const Vec3& end, float t) {
    return start + (end - start) * t;
}