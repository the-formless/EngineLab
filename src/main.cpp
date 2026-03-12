#include <iostream>
#include "math/vec3.h"
#include "renderer/sdl_window.h"
#include "renderer/framebuffer.h"

void runMathTests();
void runFrameBufferTests();

int main() {

    runMathTests();   
    runFrameBufferTests();

    FrameBuffer fb;
    SDLWindow window;

    while(window.processEvents()) {
        fb.clear(BLACK);
        fb.setPixel(400, 300, RED);

        window.present(fb);
    }
    
    return 0;
}