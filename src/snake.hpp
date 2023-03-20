#ifndef __SNAKE_HPP__
#define __SNAKE_HPP__

#include <cstddef>
#include <forward_list>
#include <SDL2/SDL.h>
#include "graphical_element.hpp"


namespace snake {
    class Snake final : public GraphicalElement {
        public:
            Snake(int x_pos, int y_pos, size_t length = 3);
            void render(SDL_Renderer *renderer) const override;
        private:
            class Segment final : public GraphicalElement {
                public:
                    Segment(int x_pos, int y_pos);
                    size_t get_length() const { return square.w; }
                    void render(SDL_Renderer *renderer) const override;
                private:
                    SDL_Rect square;
                    SDL_Color body_color {2, 100, 64, 255};
                    SDL_Color outline_color {0, 0, 0, 0};
            };
            std::forward_list<Segment> segments;
            SDL_Renderer *renderer;
    };
}

#endif
