#include <iostream>
#include <cstdint>
#include <vector>

#define WHITE 0xFFFFFFFF
#define BLACK 0xFFFFFFFF
#define RED   0xFFFFFFFF
#define GREEN 0xFFFFFFFF
#define BLUE  0xFFFFFFFF

struct FrameBuffer {
    float height, width;
    std::vector<uint32_t> pixels;

    FrameBuffer() : height(600.0f), width(800.0f){
        pixels.resize(height * width);
    }

    FrameBuffer(float h, float w) : height(h), width(w){
        pixels.resize(height * width);
    }

    inline void clear(uint32_t color) {
        for(auto& pixel : pixels) {
            pixel = color;
        }
    }

    inline void setPixel(int x, int y, uint32_t color) {
        //convert x,y to a 1d array index
        //index = y * width + x
        int index = y * width + x;
        if(x < 0 || x >= width){
            return ;
        }
        if(y < 0 || y >= height) {
            return;
        }
        
        pixels[index] = color;

    }

    inline uint32_t* data() {
        return pixels.data();
    }

    inline uint32_t pixel(int x, int y) {
        int index = y * width + x;
        return pixels[index];
    }
};