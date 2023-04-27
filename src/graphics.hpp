#ifndef __GRAPHICS_HPP__
#define __GRAPHICS_HPP__

#include <SDL2/SDL.h>
#include <memory>

#include "component.hpp"
#include "grid.hpp"

namespace snake_game {
    class Graphics {
    public:
        virtual ~Graphics() {}
        virtual void create_window(const char *title, unsigned int w,
                                   unsigned int h) = 0;
        virtual void destroy_window() = 0;
        virtual void clear() = 0;
        virtual void draw_rectangle(int x, int y, int w, int h, uint8_t r,
                                    uint8_t g, uint8_t b, uint8_t a) = 0;
        virtual void fill_rectangle(int x, int y, int w, int h, uint8_t r,
                                    uint8_t g, uint8_t b, uint8_t a) = 0;
        virtual void present() = 0;
    };

    class SDLGraphics final : public Graphics {
    public:
        SDLGraphics();
        ~SDLGraphics();
        virtual void create_window(const char *title, unsigned int w,
                                   unsigned int h) override;
        virtual void destroy_window() override;
        virtual void clear() override { SDL_RenderClear(renderer_); }
        virtual void draw_rectangle(int x, int y, int w, int h, uint8_t r,
                                    uint8_t g, uint8_t b, uint8_t a) override;
        virtual void fill_rectangle(int x, int y, int w, int h, uint8_t r,
                                    uint8_t g, uint8_t b, uint8_t a) override;
        virtual void present() override { SDL_RenderPresent(renderer_); }

    private:
        SDL_Window *window_;
        SDL_Renderer *renderer_;
    };
} // namespace snake_game

#endif
