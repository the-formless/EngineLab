#pragma once

#include "vec4.h"
#include <cmath>
#include <cassert>

struct Mat4 {
    Vec4 rows[4];

    constexpr Mat4() : rows{
        Vec4(1.0f, 0.0f, 0.0f, 0.0f), 
        Vec4(0.0f, 1.0f, 0.0f, 0.0f), 
        Vec4(0.0f, 0.0f, 1.0f, 0.0f), 
        Vec4(0.0f, 0.0f, 0.0f, 1.0f)} {}

    Mat4(Vec4 r0, Vec4 r1, Vec4 r2, Vec4 r3) : rows{r0,r1,r2,r3} {}

    inline Vec4& operator[](int i) {
        assert(i >= 0 && i < 4);
        return rows[i];
    }

    inline const Vec4& operator[](int i) const {
        return rows[i];
    }

    inline Mat4 operator+(const Mat4& other) const {
        Mat4 result;

        for(int i = 0; i < 4; i++) {
            result.rows[i] = rows[i] + other.rows[i];
        }

        return result;
    }

    inline Mat4 operator-(const Mat4& other) const {
        Mat4 result;

        for(int i = 0; i < 4; i++) {
            result.rows[i] = rows[i] - other.rows[i];
        }
        
        return result;
    }

    inline Mat4 operator*(const float scalar) const {
        Mat4 result;

        for(int i = 0; i < 4; i++) {
            result.rows[i] = rows[i] * scalar;
        }
        
        return result;
    }    

    inline Vec4 operator*(const Vec4& v) const {
        return Vec4(
            Vec4::dot(rows[0], v), 
            Vec4::dot(rows[1], v), 
            Vec4::dot(rows[2], v), 
            Vec4::dot(rows[3], v)
        );
    }

    inline Mat4 operator*(const Mat4& other) const {
        Mat4 result;
        float sum = 0.0f;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++) {
                sum = rows[i][0] * other.rows[0][j] + 
                    rows[i][1] * other.rows[1][j] +
                    rows[i][2] * other.rows[2][j] +
                    rows[i][3] * other.rows[3][j];
                result[i][j] = sum;
            }
        }
        return result;
    }

    inline Mat4 transpose() const {
        Mat4 t;
        for(int i = 0; i < 4; i++) {
            Vec4 newRow;
            for(int j = 0; j < 4; j++) {
                newRow[j] = rows[j][i];
            }
            t.rows[i] = newRow;
        }
        return t;
    }

    static inline Mat4 translation(Vec3 t) {
        return Mat4(
            Vec4(1.0f, 0.0f, 0.0f, t.x),
            Vec4(0.0f, 1.0f, 0.0f, t.y),
            Vec4(0.0f, 0.0f, 1.0f, t.z),
            Vec4(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }

    static inline Mat4 scale(Vec3 s) {
        return Mat4(
            Vec4(s.x, 0.0f, 0.0f, 0.0f),
            Vec4(0.0f, s.y, 0.0f, 0.0f),
            Vec4(0.0f, 0.0f, s.z, 0.0f),
            Vec4(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }

    static inline Mat4 rotateX(float angle) {
        float a = angle * M_PI / 180.0f;
        return Mat4(
            Vec4(1.0f, 0.0f, 0.0f, 0.0f),
            Vec4(0.0f, std::cos(a), -std::sin(a), 0.0f),
            Vec4(0.0f, std::sin(a), std::cos(a), 0.0f),
            Vec4(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }

    static inline Mat4 rotateY(float angle) {
        float a = angle * M_PI / 180.0f;
        return Mat4(
            Vec4(std::cos(a), 0.0f, std::sin(a), 0.0f),
            Vec4(0.0f, 1.0f, 0.0f, 0.0f),
            Vec4(-std::sin(a), 0.0f, std::cos(a), 0.0f),
            Vec4(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }
    static inline Mat4 rotateZ(float angle) {
        float a = angle * M_PI / 180.0f;
        return Mat4(
            Vec4(std::cos(a), -std::sin(a), 0.0f, 0.0f),
            Vec4(std::sin(a), std::cos(a), 0.0f , 0.0f),
            Vec4(0.0f, 0.0f, 1.0f, 0.0f),
            Vec4(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }
};