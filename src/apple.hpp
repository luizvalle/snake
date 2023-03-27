#ifndef __APPLE_HPP__
#define __APPLE_HPP__

#include <cstddef>
#include <SDL2/SDL.h>
#include "sprite.hpp"

namespace snake_game {
    class Apple final : public Sprite {
        public:
            Apple(size_t x, size_t y, size_t width)
                : m_bounding_box{static_cast<int>(x),
                                 static_cast<int>(y),
                                 static_cast<int>(width),
                                 static_cast<int>(width)} {}
            void render(SDL_Renderer *renderer) const override;
        private:
            const BoundingBox& _get_bounding_box() const override {
                return m_bounding_box;
            }
            BoundingBox m_bounding_box;
            SDL_Color m_fill_color {199, 55, 47, 255};
            SDL_Color m_outline_color {0, 0, 0, 255};
    };
}

#endif
