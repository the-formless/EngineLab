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
};