#include <iostream>
#include <cmath>
#include "math/vec3.h"
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

void run_math_tests()
{
    std::cout << "Running math tests...\n";

    test_dot();
    test_cross();
    test_normalize();
    test_length();
}