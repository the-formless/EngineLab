#include "vec3.h"
#include <cmath>
#include <cassert>

Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

Vec3::Vec3(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vec3 Vec3::operator+(const Vec3& other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
    return Vec3(x - other.x, y - other.y, z- other.z);
}

Vec3 Vec3::operator*(const float scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::operator/(const float divisor) const {
    assert(divisor != 0.0f);
    float inv = 1.0f/divisor;
    return Vec3(x*inv, y*inv, z*inv);
}

float Vec3::length() const {
    return std::sqrt(x*x + y*y + z*z);
} 

float Vec3::lengthSquared() const {
    return x*x + y*y + z*z;
}

Vec3 Vec3::normalize() const {
    float len = length();
    if(len == 0)
        return Vec3(0.0f,0.0f,0.0f);
    float inv = 1.0f/len;
    return Vec3(x*inv, y*inv, z*inv);
}

float Vec3::dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float Vec3::distance(const Vec3&a, const Vec3& b) {
    return (a-b).length();
}

Vec3 Vec3::cross(const Vec3& a, const Vec3& b) {
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

Vec3 Vec3::reflect(const Vec3& a, const Vec3& normal) {
    return a - normal * (2.0f * (Vec3::dot(a, normal))) ;
}

Vec3 Vec3::lerp(const Vec3& a, const Vec3& b, float t) {
    return a * (1.0f - t) + b * t;
}