#ifndef __GRAPHICS_HPP__
#define __GRAPHICS_HPP__

#include <SDL2/SDL.h>
#include "component.hpp"

namespace snake_game {
    struct Graphics {
        virtual ~Graphics() {}
        virtual void create_window(const char *title,
                                   unsigned int x,
                                   unsigned int y,
                                   unsigned int w,
                                   unsigned int h) = 0;
        virtual void destroy_window() = 0;
        virtual void clear() = 0;
        virtual void draw_rectangle(const PositionComponent& position,
                                    const RectangleRenderComponent& render) = 0;
        virtual void present() = 0;
    };

    class SDLGraphics final : public Graphics {
        public:
            SDLGraphics();
            ~SDLGraphics();
            virtual void create_window(const char *title,
                                       unsigned int x,
                                       unsigned int y,
                                       unsigned int w,
                                       unsigned int h) override;
            virtual void destroy_window() override;
            virtual void clear() override { SDL_RenderClear(m_renderer); }
            virtual void draw_rectangle(const PositionComponent& position,
                                        const RectangleRenderComponent& render) override;
            virtual void present() override { SDL_RenderPresent(m_renderer); }
        private:
            SDL_Window *m_window;
            SDL_Renderer *m_renderer;
    };
}

#endif
