#pragma once

#include<iostream>
#include <SDL2/SDL.h>
#include"framebuffer.h"

class SDLWindow {

    public:
        SDLWindow();
        ~SDLWindow();
        void present(FrameBuffer& fb);
        bool processEvents();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;



};
