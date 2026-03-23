#pragma once

#include <iostream>
#include "framebuffer.h"
#include "vertex.h"
#include "./../../tests/test_utils.h"
#include <cmath>

class Rasterizer {

    public:
        Rasterizer() = default;
        inline static void drawLine(FrameBuffer& fb, int x0, int y0, int x1, int y1, uint32_t color) {
            int dx = abs(x1 - x0);
            int dy = abs(y1 - y0);

            int error = 0;

            int sx = (x1 < x0)? -1 : 1;
            int sy = (y1 < y0)? -1 : 1;

            error = dx - dy;

            int e2;

            while(true) {
                fb.setPixel(x0, y0, color);

                if(x0 == x1 && y0 == y1)
                    break;
                
                e2 = 2 * error;

                if(e2 > -dy) {
                    error -= dy;
                    x0 += sx;
                }
                if(e2 < dx) {
                    error += dx;
                    y0 += sy; 
                }
            }
        }
        inline static void drawTriangle(FrameBuffer& fb, Vertex v0, Vertex v1, Vertex v2) {

            
            //compute triangle area
            float area = edgeFunction(v0.position.x, v0.position.y, v1, v2);

            if(floatEqual(area, 0.0f))
                return;

            //force Counter-ClockWise triangle orientation
            if(area < 0) {
                std::swap(v1,v2);
                area = -area;
            }


            //Create a bounding box and then draw a triangle
            int minX = std::min(std::min(v0.position.x, v1.position.x), v2.position.x);
            int maxX = std::max(std::max(v0.position.x, v1.position.x), v2.position.x);

            int minY = std::min(std::min(v0.position.y, v1.position.y), v2.position.y);
            int maxY = std::max(std::max(v0.position.y, v1.position.y), v2.position.y);

            //clamping bounding box to screen frame
            minX = std::max(minX, 0);
            maxX = std::min(maxX, (int)fb.width - 1);

            minY = std::max(minY, 0);
            maxY = std::min(maxY, (int)fb.height - 1);

            int dE0_dx = v1.position.y - v0.position.y;
            int dE0_dy = -(v1.position.x - v0.position.x);
            int dE1_dx = v2.position.y - v1.position.y;
            int dE1_dy = -(v2.position.x - v1.position.x);
            int dE2_dx = v0.position.y - v2.position.y;
            int dE2_dy = -(v0.position.x - v2.position.x);
            
            //compute row starts for the bounding box 
            int e0_row = edgeFunction(minX, minY, v0, v1);
            int e1_row = edgeFunction(minX, minY, v1, v2);
            int e2_row = edgeFunction(minX, minY, v2, v0);


            for(int y = minY; y <= maxY; y++) {

                    int e0 = e0_row;
                    int e1 = e1_row;
                    int e2 = e2_row;

                for(int x = minX; x <= maxX; x++){
                    if((e0 >= 0 &&
                        e1 >= 0 && 
                        e2 >= 0)
                    ){
                        float w0 = (float) e0 / area;
                        float w1 = (float) e1 / area;
                        float w2 = (float) e2 / area;

                        // Vec3 color = v0.getFloatColourVec3() * w0 + 
                        //                 v1.getFloatColourVec3() * w1 +
                        //                 v2.getFloatColourVec3() * w2;

                        Vec3 c0 = v0.getFloatColourVec3();
                        Vec3 c1 = v1.getFloatColourVec3();
                        Vec3 c2 = v2.getFloatColourVec3();

                        float invW = w0 * v0.invW + w1 * v1.invW + w2 * v2.invW;

                        Vec3 color = (c0 * v0.invW * w0 +
                                        c1 * v1.invW * w1 +
                                        c2 * v2.invW * w2) / invW;

                        // float z = w0 * v0.position.z + w1 * v1.position.z + w2 * v2.position.z;
                        float depth = 1.0f / invW;

                        if(depth < fb.depthAt(x,y)) {
                            fb.depthAt(x,y) = depth;
                            fb.setPixel(x, y, getFinalColor(color));
                        }

                    }
                    e0 += dE0_dx;
                    e1 += dE1_dx;
                    e2 += dE2_dx;
                }

                e0_row += dE0_dy;
                e1_row += dE1_dy;
                e2_row += dE2_dy;
            }

        }
        
        inline static Vertex processVertex(const Vertex& v, const Mat4& model, const Mat4& view, const Mat4& proj) {
            Vec4 world = transformVertex(v, model);
            Vec4 viewVertex = view * world;
            Vec4 clip = proj * viewVertex;
            Vec3 viewPos = {viewVertex.x, viewVertex.y, viewVertex.z};
            Vec3 divide = ndc(clip);
            Vec3 screen = viewportTransform(divide, 800, 600);
            float invW = 1.0f / clip.w;
            //return with depth
            return Vertex({
                screen.x,
                screen.y,
                clip.w
            }, viewPos, invW, v.color);
        }
    
    private:
        inline static int edgeFunction(int x, int y, Vertex a, Vertex b) {
            return (x - a.position.x ) * (b.position.y - a.position.y) - (y - a.position.y) * (b.position.x - a.position.x);
        }


        inline static Vec4 transformVertex(const Vertex& v, const Mat4& model) {
            Vec4 v4(v.position, 1.0f);
            Vec4 t = model * v4;
            return t;
        }

        inline static Vec3 ndc(const Vec4& v) {
            //NDC = normalized device coordinates
            //Perspective divide
            return {
                v.x/v.w,
                v.y/v.w,
                v.z/v.w
            };
        }

        static inline Vec3 viewportTransform(const Vec3& ndc, int width, int height) {
            float x = (ndc.x + 1.0f) * 0.5f * width;
            float y = (1.0f - ndc.y) * 0.5f * height; // flip Y (NDC up → screen down)
            float z = ndc.z; // keep as-is (we'll override with clip.w for depth)

            return { x, y, z };
        }

        inline static uint32_t getFinalColor(Vec3 color) {
            uint32_t r = (uint32_t)(color.x * 255.0f);
            uint32_t g = (uint32_t)(color.y * 255.0f);
            uint32_t b = (uint32_t)(color.z * 255.0f);

            return (255 << 24) | (r << 16) | (g << 8) | b;
        }
};