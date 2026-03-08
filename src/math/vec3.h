#pragma once

struct alignas(16) Vec3 {
    float x;
    float y;
    float z;
    float w; //Padding for alignment

    Vec3();
    Vec3(float x, float y, float z, float w = 0.0f);

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(float scalar) const;
    Vec3 operator/(float divisor) const;

    float length() const;
    float lengthSquared() const;
    Vec3 normalize() const;

    static float distance(const Vec3& a, const Vec3& b);
    static float dot(const Vec3& a, const Vec3& b);
    static Vec3 cross(const Vec3& a, const Vec3& b);
    static Vec3 reflect(const Vec3& a, const Vec3& normal);
    static Vec3 lerp(const Vec3&a, const Vec3& b, float t);
    
};