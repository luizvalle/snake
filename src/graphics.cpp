#include "graphics.hpp"

#include <SDL2/SDL.h>

#include <stdexcept>
#include <string>

namespace snake_game {
    SDLGraphics::SDLGraphics()
        : window_{nullptr}, renderer_{nullptr} {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
            std::string error_message =
                std::string("Error initializing SDL: ") + std::string(SDL_GetError());
            throw std::runtime_error(error_message);
        }
    }

    SDLGraphics::~SDLGraphics() {
        destroy_window();
        SDL_Quit();
    }

    void SDLGraphics::create_window(const char *title, unsigned int w,
                                    unsigned int h) {
        window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, w, h, 0);
        if (!window_) {
            std::string error_message =
                std::string("Error creating window: ") + std::string(SDL_GetError());
            throw std::runtime_error(error_message);
        }

        uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        renderer_ = SDL_CreateRenderer(window_, -1, flags);
        if (!renderer_) {
            std::string error_message =
                std::string("Error creating renderer: ") + std::string(SDL_GetError());
            throw std::runtime_error(error_message);
        }
    }

    void SDLGraphics::destroy_window() {
        if (renderer_) {
            SDL_DestroyRenderer(renderer_);
            renderer_ = nullptr;
        }
        if (window_) {
            SDL_DestroyWindow(window_);
            window_ = nullptr;
        }
    }

    void SDLGraphics::draw_rectangle(int x, int y, int w, int h, uint8_t r,
                                     uint8_t g, uint8_t b, uint8_t a) {
        if (!renderer_) {
            throw std::runtime_error("Render not initialized.");
        }
        SDL_Rect rect{x, y, w, h};
        SDL_SetRenderDrawColor(renderer_, r, g, b, a);
        SDL_RenderDrawRect(renderer_, &rect);
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    }

    void SDLGraphics::fill_rectangle(int x, int y, int w, int h, uint8_t r,
                                     uint8_t g, uint8_t b, uint8_t a) {
        if (!renderer_) {
            throw std::runtime_error("Render not initialized.");
        }
        SDL_Rect rect{x, y, w, h};
        SDL_SetRenderDrawColor(renderer_, r, g, b, a);
        SDL_RenderFillRect(renderer_, &rect);
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    }
} // namespace snake_game
