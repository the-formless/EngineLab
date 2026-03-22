#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include "./../math/vec3.h"
#include "./../renderer/vertex.h"


struct Triangle {
    Vec3 v0, v1, v2;
    uint32_t color;
    Triangle() : v0(Vec3()), v1(Vec3()), v2(Vec3()), color(0xffffff) {}
    Triangle(Vec3 v0, Vec3 v1, Vec3 v2, uint32_t color) : v0(v0), v1(v1), v2(v2), color(color) {}

};

struct Cell {
    Vertex v0, v1, v2, v3;
    Triangle t0, t1;
    Cell() : v0(), v1(), v2(), v3() {}
    Cell(Vertex v0, Vertex v1, Vertex v2, Vertex v3) : v0(v0), v1(v1), v2(v2), v3(v3) {}
};

struct Grid {
    int n;
    Grid() : n(10) {}
    Grid(int n) : n(n) {}

    std::vector<Cell> cells;

    inline void generate() {
        int offset = n/2;
        cells.clear();
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cells.push_back(Cell(
                    Vertex(Vec3(i-offset, j-offset, 0)),
                    Vertex(Vec3(i+1-offset, j-offset, 0)),
                    Vertex(Vec3(i-offset,j+1-offset, 0)),
                    Vertex(Vec3(i+1-offset, j+1-offset, 0))
                ));
            }
        }
    }

};