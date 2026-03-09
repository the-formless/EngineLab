#include <iostream>
#include <cmath>
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/mat4.h"
#include "test_utils.h"

bool floatEqual(float a, float b, float eps = 1e-5f) {
    return std::fabs(a-b) < eps;
}

void testDot() {
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

void testCross() {
    Vec3 a(1,0,0);
    Vec3 b(0,1,0);
    Vec3 result = Vec3::cross(a,b);

    if(floatEqual(result.x, 0.0f) && floatEqual(result.y, 0.0f) && floatEqual(result.z, 1.0f))
        {TEST_PASS("cross product");}
    else
        {TEST_FAIL("cross product");}
}

void testNormalize()
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

void testLength() {
    Vec3 v(3,4,0);
    float len = v.length();
    TEST_ASSERT(floatEqual(len, 6.0f), "Length [FAILCASE]");
}

void testDotOrthogonal() {
    Vec3 a(1,2,-1);
    Vec3 b(1,1,3);
    float dot = Vec3::dot(a,b);
    TEST_ASSERT(floatEqual(dot, 0.0f), "Dot Orthogonal");
}

void testCrossPerpendicular() {
    Vec3 a(1,0,0);
    Vec3 b(0,1,0);
    Vec3 cross = Vec3::cross(a,b);

    float dotA = Vec3::dot(a, cross);
    float dotB = Vec3::dot(b, cross);

    TEST_ASSERT((floatEqual(dotA, 0.0f) && floatEqual(dotB, 0.0f)), "Cross Perpendicular ");
}

void testReflect() {
    Vec3 i(5,-5,0);
    Vec3 n(-1,0,0);
    Vec3 r = Vec3::reflect(i,n);

    // TEST_ASSERT((r.x == -5.0f && r.y == -5.0f && r.z == 0.0f), "Reflect ");
    TEST_ASSERT((floatEqual(r.x, -5.0f) && floatEqual(r.y, -5.0f) && floatEqual(r.z, 0.0f)), "Reflect ");
}

void testLerp() {
    Vec3 a(0,0,0);
    Vec3 b(10,20,30);
    float t = 0.5f;
    Vec3 result = Vec3::lerp(a,b,t);
    TEST_ASSERT((floatEqual(result.x, 5.0f) && floatEqual(result.y, 10.0f) && floatEqual(result.z, 15.0f)), "Lerp ");
}

void testVec4Dot() {
    Vec4 a(1,2,3,4);
    Vec4 b(5,6,7,8);

    float result = Vec4::dot(a,b);

    TEST_ASSERT(floatEqual(result, 70.0f), "Vec4 dot");
}

void testMat4XVec4() {
    Mat4 I;
    Vec4 a(1,2,3,4);
    Vec4 b = I * a;
    bool equal = false;
    if(floatEqual(a.x, b.x) && floatEqual(a.y, b.y) && floatEqual(a.z, b.z) && floatEqual(a.w, b.w)){
        equal = true;
    }

    TEST_ASSERT(equal, "Identity Matrix Multiplication");
}

void testFailMat4xVec4() {
    Mat4 I;
    Vec4 a(1,2,3,4);
    Vec4 b = I * a;
    Vec4 c(1,2,3,1);
    bool equal = false;
    if(floatEqual(c.x, b.x) && floatEqual(c.y, b.y) && floatEqual(c.z, b.z) && floatEqual(c.w, b.w)){
        equal = true;
    }

    TEST_ASSERT(equal, "Identity Matrix [FAILCASE] Multiplication");
}

void testMat4XMat4() {
    Mat4 a({
        Vec4(1.0f, 0.0f, 0.0f, 10.0f),
        Vec4(0.0f, 1.0f, 0.0f, 20.0f),
        Vec4(0.0f, 0.0f, 1.0f, 30.0f),
        Vec4(0.0f, 0.0f, 0.0f, 1.0f)
    });
    Mat4 b({
        Vec4(2.0f, 0.0f, 0.0f, 0.0f),
        Vec4(0.0f, 2.0f, 0.0f, 0.0f),
        Vec4(0.0f, 0.0f, 2.0f, 0.0f),
        Vec4(0.0f, 0.0f, 0.0f, 1.0f)
    });
    Mat4 r({
        Vec4(2.0f, 0.0f, 0.0f, 10.0f),
        Vec4(0.0f, 2.0f, 0.0f, 20.0f),
        Vec4(0.0f, 0.0f, 2.0f, 30.0f),
        Vec4(0.0f, 0.0f, 0.0f, 1.0f)
    });
    Mat4 c = a * b;
    bool equalMatrix = true;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            if(c[i][j] != r[i][j])
                equalMatrix = false;
        }
    }
    TEST_ASSERT(equalMatrix, "4x4 Matrix Multiplication");
    equalMatrix = true;
    Mat4 c2 = b * a;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            if(c2[i][j] != r[i][j])
                equalMatrix = false;
        }
    }
    TEST_ASSERT(!equalMatrix, "Sequence multiplication success");
}

void testIdentityLaw() {
    Mat4 a({
        Vec4(1.0f, 0.0f, 0.0f, 10.0f),
        Vec4(0.0f, 1.0f, 0.0f, 20.0f),
        Vec4(0.0f, 0.0f, 1.0f, 30.0f),
        Vec4(0.0f, 0.0f, 0.0f, 1.0f)
    });
    Mat4 I;
    Mat4 c = I * a;
    Mat4 c2 = a * I;
    bool equalMatrix1 = true;
    bool equalMatrix2 = true;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            if(c[i][j] != a[i][j])
                equalMatrix1 = false;
            if(c2[i][j] != a[i][j])
                equalMatrix2 = false;
        }
    }
    TEST_ASSERT(equalMatrix1 && equalMatrix2, "Identity Law followed");
}

void run_math_tests()
{
    std::cout << "Running math tests...\n";

    testDot();
    testCross();
    testNormalize();
    testLength();
    testDotOrthogonal();
    testCrossPerpendicular();
    testReflect();
    testLerp();
    testVec4Dot();
    testMat4XVec4();
    testFailMat4xVec4();
    testMat4XMat4();
    testIdentityLaw();
}