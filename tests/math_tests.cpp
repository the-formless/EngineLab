#include <iostream>
#include <cmath>
#include "math/vec3.h"
#include "math/vec4.h"
#include "test_utils.h"

bool floatEqual(float a, float b, float eps = 1e-5f) {
    return std::fabs(a-b) < eps;
}

void test_dot() {
    Vec3 a(1,2,3);
    Vec3 b(4,5,6);
    float result = Vec3::dot(a,b);

    if(floatEqual(result, 32.0f)) {
        TEST_PASS("dot product");
    }
    else{
        TEST_FAIL("dot product");
    }
}

void test_cross() {
    Vec3 a(1,0,0);
    Vec3 b(0,1,0);
    Vec3 result = Vec3::cross(a,b);

    if(floatEqual(result.x, 0.0f) && floatEqual(result.y, 0.0f) && floatEqual(result.z, 1.0f))
        {TEST_PASS("cross product");}
    else
        {TEST_FAIL("cross product");}
}

void test_normalize()
{
    Vec3 v(3,0,0);
    Vec3 n = v.normalize();

    if(floatEqual(n.x,1) &&
       floatEqual(n.y,0) &&
       floatEqual(n.z,0))
        
        {TEST_PASS("normalize");}
    else
        {TEST_FAIL("normalize");}
}

void test_length() {
    Vec3 v(3,4,0);
    float len = v.length();
    TEST_ASSERT(floatEqual(len, 6.0f), "Length ");
}

void test_dot_orthogonal() {
    Vec3 a(1,2,-1);
    Vec3 b(1,1,3);
    float dot = Vec3::dot(a,b);
    TEST_ASSERT(floatEqual(dot, 0.0f), "Dot Orthogonal");
}

void test_cross_perpendicular() {
    Vec3 a(1,0,0);
    Vec3 b(0,1,0);
    Vec3 cross = Vec3::cross(a,b);

    float dotA = Vec3::dot(a, cross);
    float dotB = Vec3::dot(b, cross);

    TEST_ASSERT((floatEqual(dotA, 0.0f) && floatEqual(dotB, 0.0f)), "Cross Perpendicular ");
}

void test_reflect() {
    Vec3 i(5,-5,0);
    Vec3 n(-1,0,0);
    Vec3 r = Vec3::reflect(i,n);

    // TEST_ASSERT((r.x == -5.0f && r.y == -5.0f && r.z == 0.0f), "Reflect ");
    TEST_ASSERT((floatEqual(r.x, -5.0f) && floatEqual(r.y, -5.0f) && floatEqual(r.z, 0.0f)), "Reflect ");
}

void test_lerp() {
    Vec3 a(0,0,0);
    Vec3 b(10,20,30);
    float t = 0.5f;
    Vec3 result = Vec3::lerp(a,b,t);
    TEST_ASSERT((floatEqual(result.x, 5.0f) && floatEqual(result.y, 10.0f) && floatEqual(result.z, 15.0f)), "Lerp ");
}

void test_vec4_dot() {
    Vec4 a(1,2,3,4);
    Vec4 b(5,6,7,8);

    float result = Vec4::dot(a,b);

    TEST_ASSERT(floatEqual(result, 70.0f), "Vec4 dot");
}

void run_math_tests()
{
    std::cout << "Running math tests...\n";

    test_dot();
    test_cross();
    test_normalize();
    test_length();
    test_dot_orthogonal();
    test_cross_perpendicular();
    test_reflect();
    test_lerp();
    test_vec4_dot();
}