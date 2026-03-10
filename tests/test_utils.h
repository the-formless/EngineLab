#pragma once 

#include <iostream>
#include <cmath>

#define TEST_PASS(name) \
    std::cout << "[PASS] " << name << std::endl;

#define TEST_FAIL(name) \
    std::cout << "[FAIL] " << name << std::endl;

    #define TEST_ASSERT(condition, name) \
    if(condition) {TEST_PASS(name);} \
    else {TEST_FAIL(name);}


static bool floatEqual(float a, float b, float eps = 1e-5f) {
    return std::fabs(a-b) < eps;
}
