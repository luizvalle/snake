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
            Snake(int x, int y, size_t length, size_t width);
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
                    Segment(int x, int y, int width)
                        : m_bounding_box{x, y, width, width} {}
                    int get_x() const { return m_bounding_box.x; }
                    int get_y() const { return m_bounding_box.y; }
                    void set_x(int x) { m_bounding_box.x = x; }
                    void set_y(int y) { m_bounding_box.y = y; }
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
