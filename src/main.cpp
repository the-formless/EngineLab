#include <iostream>
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/mat4.h"
#include "renderer/sdl_window.h"
#include "renderer/framebuffer.h"
#include "renderer/rasterizer.h"
#include "scene/grid.h"
#include "scene/cube.h"
#include "scene/camera.h"

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



bool isFrontFace(Vertex v0, Vertex v1, Vertex v2) {   
    Vec3 e1 = v1.viewPos - v0.viewPos;
    Vec3 e2 = v2.viewPos - v0.viewPos;

    Vec3 normal = Vec3::cross(e1, e2);

    if(normal.z >= 0)
        return true;
    return false;
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

    Camera cam(
        {0,0,10},
        {0,0,0},
        {0,1,0},
        fov, aspect, near, far
    );

    Mat4 proj = cam.getProjectionMatrix();
    Mat4 camView = cam.getViewMatrix();

    Cube cube(1);
    cube.generate();

    while(window.processEvents()) {
        fb.clear(BLACK);
        fb.clearDepth();

        angle += 0.1f;
        Mat4 model = Mat4::rotateY(angle)  * Mat4::rotateX(angle * 0.5f);;

        // for(const auto& c : g.cells) {
        //     Vec3 tv0 = Rasterizer::processVertex(c.v0, model, camView, proj);
        //     Vec3 tv1 = Rasterizer::processVertex(c.v1, model, camView, proj);
        //     Vec3 tv2 = Rasterizer::processVertex(c.v2, model, camView, proj);
        //     Vec3 tv3 = Rasterizer::processVertex(c.v3, model, camView, proj);

        //     Rasterizer::drawTriangle(fb, tv0, tv1, tv2, WHITE);
        //     Rasterizer::drawTriangle(fb, tv2, tv1, tv3, RED);
        // }

        for(auto& f : cube.tris) {
            Vertex tv0 = Rasterizer::processVertex(f.v0, model, camView, proj);
            Vertex tv1 = Rasterizer::processVertex(f.v1, model, camView, proj);
            Vertex tv2 = Rasterizer::processVertex(f.v2, model, camView, proj);
            
            //back face culling
            if (!isFrontFace(tv0, tv1, tv2)) continue;
            Rasterizer::drawTriangle(fb, tv0, tv1, tv2);
        }
        

        window.present(fb);

    }
    
    return 0;
}

