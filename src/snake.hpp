#ifndef __SNAKE_HPP__
#define __SNAKE_HPP__

#include <cstddef>
#include <forward_list>
#include <SDL2/SDL.h>
#include "graphical_element.hpp"


namespace snake {
    class Snake final : public GraphicalElement {
        public:
            Snake(int x_pos, int y_pos);
            void render(SDL_Renderer *renderer) const override;
        private:
            class Segment final : public GraphicalElement {
                public:
                    Segment(int x_pos, int y_pos);
                    void render(SDL_Renderer *renderer) const override;
                private:
                    SDL_Rect square;
                    SDL_Color color {2, 100, 64, 255};
            };
            std::forward_list<Segment> segments;
            SDL_Renderer *renderer;
    };
}

#endif
