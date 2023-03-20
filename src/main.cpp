#include <iostream>
#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "snake.hpp"

using namespace std;

constexpr size_t WINDOW_WIDTH = 640, WINDOW_HEIGHT = 480;
constexpr int SPEED = 300;

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
        cerr << "Error initializing SDL: " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Luiz Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if (!window) {
        cerr << "Error creating window: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    uint32_t render_flags = SDL_RENDERER_ACCELERATED
                            | SDL_RENDERER_PRESENTVSYNC;

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flags);

    if (!renderer) {
        cerr << "Error creating renderer: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    snake::Snake snake {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

    SDL_RenderClear(renderer);

    snake.render(renderer);

    SDL_RenderPresent(renderer);

    SDL_PumpEvents();

    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
