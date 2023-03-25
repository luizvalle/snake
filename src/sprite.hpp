#ifndef __GRAPHICAL_ELEMENT_HPP__
#define __GRAPHICAL_ELEMENT_HPP__

#include <iterator>
#include <cstddef>
#include <SDL2/SDL.h>

namespace snake {
    struct BoundingBox final {
        BoundingBox(int x, int y, int w, int h)
            : m_x{x}, m_y{y}, m_w{w}, m_h{h} {}
        bool is_out_of_bounds(int window_width, int window_height) const {
            return (m_x <= 0 || (m_x + m_w) >= window_width || m_y <= 0
                    || (m_y + m_h) >= window_height);
        }
        bool intersects(const BoundingBox& other) const;
        int m_x, m_y, m_w, m_h;
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
