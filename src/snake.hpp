#ifndef __SNAKE_HPP__
#define __SNAKE_HPP__

#include <cstddef>
#include <list>
#include <SDL2/SDL.h>
#include "sprite.hpp"


namespace snake_game {
    enum Direction { STOPPED, UP, DOWN, LEFT, RIGHT };

    class Snake final : public Sprite {
        public:
            Snake(size_t x, size_t y, size_t length, size_t width);
            void set_direction(Direction new_direction);
            void move();
            bool self_collided() const;
            void add_segment();
            void render(SDL_Renderer *renderer) const override;
        private:
            const BoundingBox& _get_bounding_box() const override {
                return m_segments.begin()->get_bounding_box();
            }
            class Segment final {
                public:
                    Segment(size_t x, size_t y, size_t width)
                        : m_bounding_box{static_cast<int>(x),
                                         static_cast<int>(y),
                                         static_cast<int>(width),
                                         static_cast<int>(width)} {}
                    size_t get_x() const { return m_bounding_box.x; }
                    size_t get_y() const { return m_bounding_box.y; }
                    void set_x(size_t x) { m_bounding_box.x = x; }
                    void set_y(size_t y) { m_bounding_box.y = y; }
                    void render(SDL_Renderer *renderer) const;
                    const BoundingBox& get_bounding_box() const {
                        return m_bounding_box;
                    }
                private:
                    BoundingBox m_bounding_box;
                    SDL_Color m_fill_color {2, 100, 64, 255};
                    SDL_Color m_outline_color {0, 0, 0, 0};
            };
            std::list<Segment> m_segments;
            const size_t m_width;
            Direction direction = STOPPED;
    };
}

#endif
