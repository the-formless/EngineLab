#pragma once 
#include <cstdint>
#include "./../math/vec3.h"

struct Vertex {
    Vec3 position;
    Vec3 viewPos;
    uint32_t color;
    float invW;

    Vertex() : position(Vec3()), viewPos(Vec3()), color(0xFFFFFFFF) {}
    Vertex(Vec3 position) : position(position), viewPos(Vec3()), color(0xFFFFFFFF) {}
    Vertex(Vec3 position, Vec3 viewPos, float invW, uint32_t color) : position(position), viewPos(viewPos), invW(invW), color(color) {}
    Vertex(Vec3 position, uint32_t color) : position(position), viewPos(Vec3()), color(color) {}

    inline Vec3 getFloatColourVec3() {
        
        float a = static_cast<float>((color >> 24) & 0xFF) / 255.0f;
        float r = static_cast<float>((color >> 16) & 0xFF) / 255.0f;
        float g = static_cast<float>((color >> 8) & 0xFF) / 255.0f;
        float b = static_cast<float>((color) & 0xFF) / 255.0f;

        //discarding alpha. can later change to vec4 if a is required
        return Vec3(r, g, b);

    }
};