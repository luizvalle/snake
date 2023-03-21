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
            Snake(int x_pos, int y_pos, size_t length = 3, int width = 20,
                    int speed = 100);
            void change_direction(Direction direction);
            void move();
            void render(SDL_Renderer *renderer) const override;
        private:
            class Segment final : public Sprite {
                public:
                    Segment(int x_pos, int y_pos, int width);
                    int get_x() const { return segment.x; }
                    int get_y() const { return segment.y; }
                    void set_x(int x) { segment.x = x; }
                    void set_y(int y) { segment.y = y; }
                    void render(SDL_Renderer *renderer) const override;
                private:
                    SDL_Rect segment;
                    SDL_Color fill_color {2, 100, 64, 255};
                    SDL_Color outline_color {0, 0, 0, 0};
            };
            std::list<Segment> segments;
            int width;
            int speed;
            int x_vel = 0, y_vel = 0;
    };
}

#endif
