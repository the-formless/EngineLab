#pragma once

#include <iostream>
#include <cstdint>
#include <vector>

#define WHITE 0xFFFFFFFF
#define BLACK 0xFF000000
#define RED   0xFFFF0000
#define GREEN 0xFF00FF00
#define BLUE  0xFF0000FF
#define CYAN  0x00FFFF
#define ORANGE 0xFFA500

struct FrameBuffer {
    int width;
    int height;
    std::vector<uint32_t> pixels;
    std::vector<float> depth;

    FrameBuffer() : width(800), height(600){
        pixels.resize(height * width);
        depth.resize(height * width);
    }
    
    FrameBuffer(int w, int h) : width(w), height(h){
        pixels.resize(height * width);
        depth.resize(height * width);
    }

    inline void clear(uint32_t color) {
        for(auto& pixel : pixels) {
            pixel = color;
        }
    }

    inline void setPixel(int x, int y, uint32_t color) {
        //convert x,y to a 1d array index
        //index = y * width + x
        if(x < 0 || x >= width){
            return ;
        }
        if(y < 0 || y >= height) {
            return;
        }
        
        int index = y * width + x;
        pixels[index] = color;

    }

    inline uint32_t* data() {
        return pixels.data();
    }

    inline uint32_t pixel(int x, int y) {
        int index = y * width + x;
        return pixels[index];
    }

    inline void clearDepth(float value = std::numeric_limits<float>::infinity()) {
        for(auto& d: depth) {
            d = value;
        }
    }

    inline float& depthAt(int x, int y) {
        return depth[y * width + x];
    }
};