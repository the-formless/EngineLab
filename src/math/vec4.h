#pragma once
#include <cmath>
#include <cassert>

struct Vec4 {
    float x, y, z, w;

    Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Vec4(Vec3 v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}

    inline Vec4 operator+(const Vec4& other) const {
        return Vec4(x+other.x, y+other.y, z+other.z, w+other.w);
    }

    inline Vec4 operator-(const Vec4& other) const {
        return Vec4(x-other.x, y-other.y, z-other.z, w-other.w);
    }

    inline Vec4 operator*(const float scalar) const {
        return Vec4(x*scalar, y*scalar, z*scalar, w*scalar);
    }

    inline Vec4 operator/(const float divisor) const {
        float inv = 1.0f/divisor;
        return Vec4(x*inv, y*inv, z*inv, w*inv);
    }

    inline float operator[](int i) const {
        switch(i){
            case 0: 
            return x;
            case 1:
            return y;
            case 2:
            return z;
            case 3:
            return w;
            default:
            return 0.0f;
        }
    }

    inline float& operator[](int i) {
        return (&x)[i];
    }

    inline float length() const {
        return std::sqrt(x*x + y*y + z*z + w*w);
    }

    inline float lengthSquared() const {
        return x*x + y*y +z*z + w*w;
    }

    inline Vec4 normalize() const {
        float len = length();
        float lenInv = 1.0f/len;
        return Vec4(x*lenInv, y*lenInv, z*lenInv, w*lenInv);
    }

    static inline float dot(const Vec4& a, const Vec4& b) {
        return (a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w);
    }

};