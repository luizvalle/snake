#include <cstdint>
#include <algorithm>
#include <functional>
#include <SDL2/SDL.h>
#include "window.hpp"

namespace snake {
    Window::Window(int width, int height, std::string name)
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
            // TODO: Error
        }

        window = SDL_CreateWindow(name.c_str(),
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                width, height, 0);

        if (!window) {
            // TODO: Error
        }

        uint32_t render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

        renderer = SDL_CreateRenderer(window, -1, render_flags);

        if (!renderer) {
            // TODO: Error
        }
    }

    Window::~Window()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}
