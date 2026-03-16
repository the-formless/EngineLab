#pragma once

#include <iostream>
#include "framebuffer.h"
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
        inline static void drawTriangle(FrameBuffer& fb, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
            int minX = std::min(std::min(x0, x1), x2);
            int maxX = std::max(std::max(x0, x1), x2);

            int minY = std::min(std::min(y0, y1), y2);
            int maxY = std::max(std::max(y0, y1), y2);

            for(int y = minY; y <= maxY; y++) {
                for(int x = minX; x <= maxX; x++){
                    int e0 = edgeFunction(x, y, x0, y0, x1, y1);
                    int e1 = edgeFunction(x, y, x1, y1, x2, y2);
                    int e2 = edgeFunction(x, y, x2, y2, x0, y0);
                    if((e0 >= 0 &&
                        e1 >= 0 && 
                        e2 >= 0) ||
                        (e0 <= 0 &&
                        e1 <= 0 && 
                        e2 <= 0)
                    ){
                        fb.setPixel(x, y, color);
                    }
                }
            }

        }
    
    private:
        inline static int edgeFunction(int x, int y, int ex0, int ey0, int ex1, int ey1) {
            return (x - ex0 ) * (ey1 - ey0) - (y - ey0) * (ex1 - ex0);
        }
};
