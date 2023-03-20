#include <utility>
#include <algorithm>
#include <functional>
#include <SDL2/SDL.h>
#include "snake.hpp"

using namespace snake;

Snake::Snake(int x_pos, int y_pos, size_t length)
{
    while (length--) {
        Snake::Segment segment {x_pos, y_pos};
        segments.push_front(std::move(segment));
        x_pos -= segment.get_length();
    }
}

void Snake::render(SDL_Renderer *renderer) const
{
    std::for_each(
            segments.begin(), segments.end(),
            std::bind(&Segment::render, std::placeholders::_1, renderer));
}

Snake::Segment::Segment(int x_pos, int y_pos)
    : square{x_pos, y_pos, 10, 10} {}

void Snake::Segment::render(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(
            renderer, body_color.r, body_color.g, body_color.b, body_color.a); 
    SDL_RenderFillRect(renderer, &square);
    SDL_SetRenderDrawColor(
            renderer, outline_color.r, outline_color.g, outline_color.b,
            outline_color.a); 
    SDL_RenderDrawRect(renderer, &square);
}
