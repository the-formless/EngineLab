#pragma once 
#include "./../math/vec3.h"

struct Vertex {
    Vec3 position;
    float invW;

    Vertex() : position(Vec3()) {}
    Vertex(Vec3 position) : position(position) {}
    Vertex(Vec3 position, float invW) : position(position), invW(invW) {}

};