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

Vec3 transformVertex(const Vec3& v, Mat4 model) {
    Vec4 v4(v, 1.0f);
    Vec4 t = model * v4;
    return Vec3(t.x, t.y, t.z);
}

Vec3 project(Vec3 v, float scale, int width, int height) {
    return {
        v.x * scale + width/2,
    -v.y * scale + height/2,
    0
    };
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
    float scale = 55.0f;

    while(window.processEvents()) {
        fb.clear(BLACK);
        fb.setPixel(400, 300, RED);

        Rasterizer::drawLine(fb, 100, 100, 700, 100, GREEN);
        Rasterizer::drawLine(fb, 100, 100, 100, 500, RED);
        Rasterizer::drawLine(fb, 200, 200, 700, 500, BLUE);
        Rasterizer::drawLine(fb, 700, 500, 100, 100, WHITE);
        Rasterizer::drawLine(fb, 400, 100, 200, 500, GREEN);
        Rasterizer::drawLine(fb, 300, 500, 400, 100, BLUE);

        // Rasterizer::drawTriangle(fb, 200,100,100,400,500,400, WHITE);
        Rasterizer::drawTriangle(fb, 10,10,300,40,40,400, GREEN);

        angle += 0.1f;
        Mat4 model = Mat4::rotateY(angle)  * Mat4::rotateX(angle * 0.5f);;

        for(const auto& c : g.cells) {
        //     Vec3 tv0 = transformVertex(c.v0, model);
        //     Vec3 tv1 = transformVertex(c.v1, model);
        //     Vec3 tv2 = transformVertex(c.v2, model);
        //     Vec3 tv3 = transformVertex(c.v3, model);
            Vec3 tv0 = project(transformVertex(c.v0, model), scale, width, height);
            Vec3 tv1 = project(transformVertex(c.v1, model), scale, width, height);
            Vec3 tv2 = project(transformVertex(c.v2, model), scale, width, height);
            Vec3 tv3 = project(transformVertex(c.v3, model), scale, width, height);

            Rasterizer::drawTriangle(fb, tv0.x, tv0.y, tv1.x, tv1.y, tv2.x, tv2.y, WHITE);
            Rasterizer::drawTriangle(fb, tv2.x, tv2.y, tv1.x, tv1.y, tv3.x, tv3.y, RED);
        }
        

        window.present(fb);

    }
    
    return 0;
}
