#include <iostream>
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/mat4.h"
#include "renderer/sdl_window.h"
#include "renderer/framebuffer.h"
#include "renderer/rasterizer.h"
#include "grid/grid.h"

void runMathTests();
void runFrameBufferTests();
// void drawLine(FrameBuffer& fb, int x0, int y0, int x1, int y1, uint32_t color);


Vec3 projectOrtho(Vec3 v, float scale, int width, int height) {
    return {
        v.x * scale + width/2,
    -v.y * scale + height/2,
    v.z
    };
}
//just implemented perspective projection
Vec3 projectPerspective(Vec3 v, float scale, int width, int height) {
    float z = v.z + 10.0f; //move camera back
    float x = (v.x/z) * scale + width/2;
    float y = (-v.y/z) * scale + height/2;
    return {x,y,z};
}


// Function to convert degrees to radians
float degreesToRadians(float degrees) {
    // Cast M_PI to float for consistency, or use double for better precision
    return degrees * static_cast<float>(M_PI) / 180.0f; 
}





int main() {

    runMathTests();   
    runFrameBufferTests();
    int width = 800, height = 600;
    FrameBuffer fb(width, height);
    SDLWindow window;
    Grid g(10);
    g.generate();
    static float angle = 0.0f;
    float scale = 150.0f;

    float fov = degreesToRadians(60.0f);
    float aspect = (float)width / height;
    float near = 0.1f;
    float far = 100.0f;

    Mat4 proj = Mat4::perspective(fov, aspect, near, far);
    Mat4 view(
        {-1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, -1.0f, -20.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    );

    while(window.processEvents()) {
        fb.clear(BLACK);
        fb.clearDepth();
        fb.setPixel(400, 300, RED);

        Rasterizer::drawLine(fb, 100, 100, 700, 100, GREEN);
        Rasterizer::drawLine(fb, 100, 100, 100, 500, RED);
        Rasterizer::drawLine(fb, 200, 200, 700, 500, BLUE);
        Rasterizer::drawLine(fb, 700, 500, 100, 100, WHITE);
        Rasterizer::drawLine(fb, 400, 100, 200, 500, GREEN);
        Rasterizer::drawLine(fb, 300, 500, 400, 100, BLUE);

        // Rasterizer::drawTriangle(fb, 200,100,100,400,500,400, WHITE);
        // Rasterizer::drawTriangle(fb, 10,10,300,40,40,400, GREEN);

        angle += 0.1f;
        Mat4 model = Mat4::rotateY(angle)  * Mat4::rotateX(angle * 0.5f);;

        for(const auto& c : g.cells) {
            Vec3 tv0 = Rasterizer::processVertex(c.v0, model, view, proj);
            Vec3 tv1 = Rasterizer::processVertex(c.v1, model, view, proj);
            Vec3 tv2 = Rasterizer::processVertex(c.v2, model, view, proj);
            Vec3 tv3 = Rasterizer::processVertex(c.v3, model, view, proj);

            Rasterizer::drawTriangle(fb, tv0, tv1, tv2, WHITE);
            Rasterizer::drawTriangle(fb, tv2, tv1, tv3, RED);
        }
        

        window.present(fb);

    }
    
    return 0;
}
