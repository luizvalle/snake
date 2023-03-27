#ifndef __GRAPHICAL_ELEMENT_HPP__
#define __GRAPHICAL_ELEMENT_HPP__

#include <cstddef>
#include <iterator>
#include <SDL2/SDL.h>

namespace snake_game {
    struct BoundingBox final : SDL_Rect {
        bool is_out_of_bounds(size_t window_width, size_t window_height) const {
            return (x <= 0 || (x + w) >= window_width || y <= 0
                    || (y + h) >= window_height);
        }
        bool intersects(const BoundingBox& other) const;
    };
    struct Sprite {
    public:
        virtual void render(SDL_Renderer *renderer) const = 0;
        bool is_out_of_bounds(size_t window_width, size_t window_height) const {
            return _get_bounding_box().is_out_of_bounds(window_width,
                                                       window_height);
        }
        bool collided_with(const Sprite& other) const {
            return _get_bounding_box().intersects(other._get_bounding_box());
        }
    private:
        virtual const BoundingBox& _get_bounding_box() const = 0;
    };
}

#endif
