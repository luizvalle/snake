#include "graphics.hpp"

#include <SDL2/SDL.h>

#include <stdexcept>
#include <string>

namespace snake_game {
SDLGraphics::SDLGraphics() : m_window{nullptr}, m_renderer{nullptr} {
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

void SDLGraphics::create_window(const char* title, unsigned int w,
                                unsigned int h) {
  m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, w, h, 0);
  if (!m_window) {
    std::string error_message =
        std::string("Error creating window: ") + std::string(SDL_GetError());
    throw std::runtime_error(error_message);
  }

  uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  m_renderer = SDL_CreateRenderer(m_window, -1, flags);
  if (!m_renderer) {
    std::string error_message =
        std::string("Error creating renderer: ") + std::string(SDL_GetError());
    throw std::runtime_error(error_message);
  }
}

void SDLGraphics::destroy_window() {
  if (m_renderer) {
    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
  }
  if (m_window) {
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
  }
}

void SDLGraphics::draw_rectangle(const PositionComponent& position,
                                 const RectangleRenderComponent& render) {
  if (!m_renderer) {
    throw std::runtime_error("Render not initialized.");
  }
  SDL_Rect rect{position.x, position.y, render.rect.w, render.rect.h};
  SDL_SetRenderDrawColor(m_renderer, render.fill_color.r, render.fill_color.g,
                         render.fill_color.b, render.fill_color.a);
  SDL_RenderFillRect(m_renderer, &rect);
  SDL_SetRenderDrawColor(m_renderer, render.border_color.r,
                         render.border_color.g, render.border_color.b,
                         render.border_color.a);
  SDL_RenderDrawRect(m_renderer, &rect);
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
}
}  // namespace snake_game
