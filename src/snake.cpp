#include <utility>
#include <algorithm>
#include <functional>
#include <SDL2/SDL.h>
#include "snake.hpp"

using namespace snake;

Snake::Snake(int x_pos, int y_pos)
{
    Snake::Segment segment {x_pos, y_pos};
    segments.push_front(std::move(segment));
}

void Snake::render(SDL_Renderer *renderer) const
{
    std::for_each(
            segments.begin(), segments.end(),
            std::bind(&Segment::render, std::placeholders::_1, renderer));
}

Snake::Segment::Segment(int x_pos, int y_pos)
    : square{ x_pos, y_pos, 10, 10 } {}

void Snake::Segment::render(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(
            renderer, color.r, color.g, color.b, color.a); 
    SDL_RenderFillRect(renderer, &square);
}
