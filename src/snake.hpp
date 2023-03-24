#ifndef __SNAKE_HPP__
#define __SNAKE_HPP__

#include <cstddef>
#include <list>
#include <SDL2/SDL.h>
#include "sprite.hpp"


namespace snake {
    enum Direction { UP, DOWN, LEFT, RIGHT };

    class Snake final : public Sprite {
        public:
            Snake(int x_pos, int y_pos, size_t length, int width);
            void change_direction(Direction direction);
            void move();
            void render(SDL_Renderer *renderer) const override;
        private:
            class Segment final {
                public:
                    Segment(int x, int y, int width);
                    int get_x() const { return m_segment.x; }
                    int get_y() const { return m_segment.y; }
                    void set_x(int x) { m_segment.x = x; }
                    void set_y(int y) { m_segment.y = y; }
                    void render(SDL_Renderer *renderer) const;
                private:
                    SDL_Rect m_segment;
                    SDL_Color m_fill_color {2, 100, 64, 255};
                    SDL_Color m_outline_color {0, 0, 0, 0};
            };
            std::list<Segment> m_segments;
            int m_width;
            int m_speed;
            int m_x_vel = 0, m_y_vel = 0;
    };
}

#endif
