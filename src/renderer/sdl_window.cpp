#include <iostream>
#include "sdl_window.h"

SDLWindow::SDLWindow() {
    int result = SDL_Init(SDL_INIT_VIDEO);
    if(result == 0) {
        std::cout << "Init Successful \n";
    } else {
        std::cout << "Init unsuccessful \n";
    }
    window = SDL_CreateWindow("EngineLab", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 800, 600);

    if(window == nullptr || renderer == nullptr || texture == nullptr)
        std::cout<<SDL_GetError()<<std::endl;
}

SDLWindow::~SDLWindow() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLWindow::present(FrameBuffer& fb) {
    SDL_UpdateTexture(texture, nullptr, fb.data(), fb.width * sizeof(uint32_t));
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

bool SDLWindow::processEvents() {
    SDL_Event event;
    std::cout<<"starting while loop !!! \n";
    while(SDL_PollEvent(&event)){
        std::cout<<"while reached !!! \n";
        if(event.type == SDL_KEYDOWN)
            std::cout<<"Key Pressed !!! \n";
        if(event.type == SDL_QUIT)
            return false;
    }
    return true;
}