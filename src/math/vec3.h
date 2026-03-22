#pragma once

#include <cmath>
#include <cassert>

struct alignas(16) Vec3 {
    float x;
    float y;
    float z;
    float w; //Padding for alignment

    Vec3() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

    Vec3(float x, float y, float z, float w = 0.0f) : x(x), y(y), z(z), w(w) {}

    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z- other.z);
    }

    Vec3 operator*(const float scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    Vec3 operator/(const float divisor) const {
        assert(divisor != 0.0f);
        float inv = 1.0f/divisor;
        return Vec3(x*inv, y*inv, z*inv);
    }

    inline float length() const {
        return std::sqrt(x*x + y*y + z*z);
    } 

    inline float lengthSquared() const {
        return x*x + y*y + z*z;
    }

    inline Vec3 normalize() const {
        float len = length();
        if(len == 0)
            return Vec3(0.0f,0.0f,0.0f);
        float inv = 1.0f/len;
        return Vec3(x*inv, y*inv, z*inv);
    }

    static inline float dot(const Vec3& a, const Vec3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    static inline float distance(const Vec3&a, const Vec3& b) {
        return (a-b).length();
    }

    static inline Vec3 cross(const Vec3& a, const Vec3& b) {
        return Vec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    static inline Vec3 reflect(const Vec3& a, const Vec3& normal) {
        return a - normal * (2.0f * (Vec3::dot(a, normal))) ;
    }

    static inline Vec3 lerp(const Vec3& a, const Vec3& b, float t) {
        return a * (1.0f - t) + b * t;
    }
    
    static inline void debugPrint(Vec3 p) {
        std::cout << "x: " <<p.x<< ", y: "<< p.y <<", z: "<<p.z<<std::endl;
    }
};