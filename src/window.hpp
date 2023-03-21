#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <string>
#include <SDL2/SDL.h>
#include "sprite.hpp"

namespace snake {
  class Window final {
    public:
      Window(int window, int height, std::string name);
      Window(const Window&) = delete;
      Window& operator=(Window) = delete;
      Window(const Window&&) = delete;
      Window& operator=(Window&&) = delete;
      ~Window();
      void clear() { SDL_RenderClear(renderer); }
      void render(const Sprite& sprite) { sprite.render(renderer); }
      void show() { SDL_RenderPresent(renderer); };
    private:
      SDL_Window *window;
      SDL_Renderer *renderer;
  };
}

#endif
