#include <iostream>
#include "test_utils.h"
#include "./../src/renderer/framebuffer.h"

void testFrameBuffer() {
    FrameBuffer fb(10,10);

    fb.clear(RED);

    bool test = false;
    if(fb.pixel(0,0) == RED && fb.pixel(9,9) == RED)
        test = true;
    TEST_ASSERT(test, "Pixels Setting ");

    fb.setPixel(5,5, BLUE);

    TEST_ASSERT((fb.pixel(5,5) == BLUE), "Change Pixel ");

}

void runFrameBufferTests() {
    std::cout << "Running frame buffer tests...\n";

    testFrameBuffer();
}

