#ifndef __GRAPHICAL_ELEMENT_HPP__
#define __GRAPHICAL_ELEMENT_HPP__

#include <iterator>
#include <cstddef>
#include <SDL2/SDL.h>

namespace snake_game {
    struct BoundingBox final : SDL_Rect {
        bool is_out_of_bounds(int window_width, int window_height) const {
            return (x <= 0 || (x + w) >= window_width || y <= 0
                    || (y + h) >= window_height);
        }
        bool intersects(const BoundingBox& other) const;
    };
    struct Sprite {
    public:
        virtual void render(SDL_Renderer *renderer) const = 0;
        bool is_out_of_bounds(int window_width, int window_height) {
            return _get_bounding_box().is_out_of_bounds(window_width,
                                                       window_height);
        }
    private:
        virtual const BoundingBox& _get_bounding_box() const = 0;
    };
}

#endif
