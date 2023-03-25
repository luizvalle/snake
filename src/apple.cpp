#include "apple.hpp"

namespace snake_game {
    void Apple::render(SDL_Renderer *renderer) const {
        SDL_SetRenderDrawColor(renderer,
                m_fill_color.r,
                m_fill_color.g,
                m_fill_color.b,
                m_fill_color.a);
        SDL_RenderFillRect(renderer, &m_bounding_box);
        SDL_SetRenderDrawColor(renderer,
                m_outline_color.r,
                m_outline_color.g,
                m_outline_color.b,
                m_outline_color.a);
        SDL_RenderDrawRect(renderer, &m_bounding_box);
    }
}
