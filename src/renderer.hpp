#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <stdexcept>
#include <SDL2/SDL.h>

namespace snake_game {
    class Renderer final {
        public:
            ~Renderer() {
                if (m_renderer) {
                    SDL_DestroyRenderer(m_renderer);
                    m_renderer = nullptr;
                }
            }

            static Renderer& get_instance() {
                static Renderer instance;
                return instance;
            }

            void init(SDL_Window *window) {
                uint32_t render_flags = (SDL_RENDERER_ACCELERATED
                        | SDL_RENDERER_PRESENTVSYNC);
                m_renderer = SDL_CreateRenderer(window, -1, render_flags);
                if (!m_renderer) {
                    throw new std::runtime_error("Cannot create renderer.");
                }
            }

            SDL_Renderer *get() { return m_renderer; }
        private:
            Renderer() : m_renderer{nullptr} {}
            SDL_Renderer *m_renderer;
    };
}

#endif
