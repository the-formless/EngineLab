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
};
