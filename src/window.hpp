#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <string>
#include <SDL2/SDL.h>
#include "sprite.hpp"

namespace snake_game {
  class Window final {
    public:
      Window(int window, int height, std::string name);
      Window(const Window&) = delete;
      Window& operator=(Window) = delete;
      Window(const Window&&) = delete;
      Window& operator=(Window&&) = delete;
      ~Window();
      void clear() { SDL_RenderClear(m_renderer); }
      void render(const Sprite& sprite) {
          sprite.render(m_renderer);
          SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
      }
      void show() { SDL_RenderPresent(m_renderer); };
    private:
      SDL_Window *m_window;
      SDL_Renderer *m_renderer;
  };
}

#endif
