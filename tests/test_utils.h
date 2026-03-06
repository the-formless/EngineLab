#pragma once 

#include <iostream>

#define TEST_PASS(name) \
    std::cout << "[PASS] " << name << std::endl;

#define TEST_FAIL(name) \
    std::cout << "[FAIL] " << name << std::endl;

    #define TEST_ASSERT(condition, name) \
    if(condition) {TEST_PASS(name);} \
    else {TEST_FAIL(name);}