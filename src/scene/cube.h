#pragma once
#include <vector>
#include <cstdint>
#include "./../renderer/vertex.h"
#include "./../renderer/framebuffer.h"
#include "./../math/vec3.h"

struct Triangle {
    Vertex v0, v1, v2;
    uint32_t color;
    Triangle() : v0(), v1(), v2(), color(0xFFFFFF) {}
    Triangle(Vertex v0, Vertex v1, Vertex v2, uint32_t color) : v0(v0), v1(v1), v2(v2), color(color) {}
};

struct Cube {
    int size;
    Cube() : size(5) {}
    Cube(int size) : size(size) {}

    std::vector<Triangle> tris;

    inline void generate() {
        Vertex v0(Vec3(-1.0f, 1.0f, -1.0f) * size, RED), 
        v1(Vec3(1.0f, 1.0f, -1.0f) * size, GREEN), 
        v2(Vec3(-1.0f, -1.0f, -1.0f) * size, BLUE), 
        v3(Vec3(1.0f, -1.0f, -1.0f) * size, CYAN), 
        v4(Vec3(1.0f, 1.0f, 1.0f) * size, WHITE), 
        v5(Vec3(1.0f, -1.0f, 1.0f) * size, ORANGE), 
        v6(Vec3(-1.0f, 1.0f, 1.0f) * size, BLUE), 
        v7(Vec3(-1.0f, -1.0f, 1.0f) * size, GREEN);

        tris.clear();

        // front (-Z)
        tris.push_back({v0, v1, v2, WHITE});
        tris.push_back({v2, v1, v3, WHITE});

        // right (+X)
        tris.push_back({v1, v4, v3, GREEN});
        tris.push_back({v3, v4, v5, GREEN});

        // back (+Z)
        tris.push_back({v4, v6, v5, BLUE});
        tris.push_back({v5, v6, v7, BLUE});

        // left (-X)
        tris.push_back({v6, v0, v7, RED});
        tris.push_back({v7, v0, v2, RED});

        // bottom (-Y)
        tris.push_back({v2, v3, v7, CYAN});
        tris.push_back({v7, v3, v5, CYAN});

        // top (+Y)
        tris.push_back({v6, v4, v0, ORANGE});
        tris.push_back({v0, v4, v1, ORANGE});
        
    }
};