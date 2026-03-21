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

Vec4 transformVertex(const Vec3& v, Mat4 model) {
    Vec4 v4(v, 1.0f);
    Vec4 t = model * v4;
    return t;
}

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

Vec3 ndc(const Vec4& v) {
    //Perspective divide
    return {
        v.x/v.w,
        v.y/v.w,
        v.z/v.w
    };
}

inline Vec3 viewportTransform(const Vec3& ndc, int width, int height) {
    float x = (ndc.x + 1.0f) * 0.5f * width;
    float y = (1.0f - ndc.y) * 0.5f * height; // flip Y (NDC up → screen down)
    float z = ndc.z; // keep as-is (we'll override with clip.w for depth)

    return { x, y, z };
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
            Vec4 world0 = transformVertex(c.v0, model);
            Vec4 world1 = transformVertex(c.v1, model);
            Vec4 world2 = transformVertex(c.v2, model);
            Vec4 world3 = transformVertex(c.v3, model);

            world0.z -= 25.0f;
            world1.z -= 25.0f;
            world2.z -= 25.0f;
            world3.z -= 25.0f;

            Vec4 clip0 = proj * world0;
            Vec4 clip1 = proj * world1;
            Vec4 clip2 = proj * world2;
            Vec4 clip3 = proj * world3;
            
            if (clip0.w <= 0.0f || clip1.w <= 0.0f || clip2.w <= 0.0f || clip3.w <= 0.0f) continue;

            // std::cout << clip0.x << " " << clip0.y << " " << clip0.w << std::endl;
            Vec3 ndc0 = ndc(clip0);
            Vec3 ndc1 = ndc(clip1);
            Vec3 ndc2 = ndc(clip2);
            Vec3 ndc3 = ndc(clip3);

            // Vec3 tv0 = projectPerspective({world0.x, world0.y, world0.z}, scale, width, height);
            // Vec3 tv1 = projectPerspective({world1.x, world1.y, world1.z}, scale, width, height);
            // Vec3 tv2 = projectPerspective({world2.x, world2.y, world2.z}, scale, width, height);
            // Vec3 tv3 = projectPerspective({world3.x, world3.y, world3.z}, scale, width, height);
            Vec3 tv0 = viewportTransform(ndc0, width, height);
            Vec3 tv1 = viewportTransform(ndc1, width, height);
            Vec3 tv2 = viewportTransform(ndc2, width, height);
            Vec3 tv3 = viewportTransform(ndc3, width, height);
            // Vec3 tv0 = viewportTransform((Vec3)clip0, width, height);
            // Vec3 tv1 = viewportTransform((Vec3)clip1, width, height);
            // Vec3 tv2 = viewportTransform((Vec3)clip2, width, height);
            // Vec3 tv3 = viewportTransform((Vec3)clip3, width, height);

            tv0.z = clip0.w;
            tv1.z = clip1.w;
            tv2.z = clip2.w;
            tv3.z = clip3.w;

            Rasterizer::drawTriangle(fb, tv0, tv1, tv2, WHITE);
            Rasterizer::drawTriangle(fb, tv2, tv1, tv3, RED);
        }
        

        window.present(fb);

    }
    
    return 0;
}
