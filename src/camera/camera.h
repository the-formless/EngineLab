#pragma once

#include <iostream>
#include "./../math/vec3.h"
#include "./../math/mat4.h"

struct Camera {
    Vec3 position, target, up;
    float fov, aspect, near, far;

    // Camera(Vec3 position) : position(position) {}
    Camera(Vec3 position, Vec3 target, Vec3 up, float fov, float aspect, float near, float far) 
        : position(position), target(target), up(up), fov(fov), aspect(aspect), near(near), far(far) {}

    inline Mat4 getViewMatrix() {
        Vec3 z = (position - target).normalize(); //camera backward
        Vec3 x = Vec3::cross(up, z).normalize(); //right
        Vec3 y = Vec3::cross(z, x).normalize(); //true up

        return Mat4 (
            Vec4(x.x, x.y, x.z, -Vec3::dot(x, position)),
            Vec4(y.x, y.y, y.z, -Vec3::dot(y, position)),
            Vec4(z.x, z.y, z.z, -Vec3::dot(z, position)),
            Vec4(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }

    inline Mat4 getProjectionMatrix() {
        return Mat4::perspective(fov, aspect, near, far);
    }

};