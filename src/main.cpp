#include <iostream>
#include "math/vec3.h"
#include "renderer/sdl_window.h"
#include "renderer/framebuffer.h"
#include "renderer/rasterizer.h"

void runMathTests();
void runFrameBufferTests();
// void drawLine(FrameBuffer& fb, int x0, int y0, int x1, int y1, uint32_t color);

int main() {

    runMathTests();   
    runFrameBufferTests();

    FrameBuffer fb;
    SDLWindow window;

    while(window.processEvents()) {
        fb.clear(BLACK);
        fb.setPixel(400, 300, RED);

        Rasterizer::drawLine(fb, 100, 100, 700, 100, GREEN);
        Rasterizer::drawLine(fb, 100, 100, 100, 500, RED);
        Rasterizer::drawLine(fb, 200, 200, 700, 500, BLUE);
        Rasterizer::drawLine(fb, 700, 500, 100, 100, WHITE);
        Rasterizer::drawLine(fb, 400, 100, 200, 500, GREEN);
        Rasterizer::drawLine(fb, 300, 500, 400, 100, BLUE);

        window.present(fb);

    }
    
    return 0;
}