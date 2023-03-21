#include <utility>
#include <algorithm>
#include <functional>
#include <SDL2/SDL.h>
#include "snake.hpp"

using namespace snake;

Snake::Snake(int x_pos, int y_pos, size_t length, int w, int sp)
    : width{w}, speed{w}
{
    while (length--) {
        Snake::Segment segment {x_pos, y_pos, width};
        segments.push_back(std::move(segment));
        x_pos -= width;
    }
}

void Snake::change_direction(Direction direction)
{
    switch (direction) {
        case UP:
            x_vel = 0;
            y_vel = -speed;
            break;
        case DOWN:
            x_vel = 0;
            y_vel = speed;
            break;
        case LEFT:
            x_vel = -speed;
            y_vel = 0;
            break;
        case RIGHT:
            x_vel = speed;
            y_vel = 0;
            break;
    }
}

void Snake::move()
{
    auto segment = segments.begin();
    int prev_x = segment->get_x(), prev_y = segment->get_y();
    segment->set_x(prev_x + x_vel);
    segment->set_y(prev_y + y_vel);
    while (++segment != segments.end()) {
        int tmp_x = segment->get_x(), tmp_y = segment->get_y();
        segment->set_x(prev_x);
        segment->set_y(prev_y);
        prev_x = tmp_x;
        prev_y = tmp_y;
    }
}

void Snake::render(SDL_Renderer *renderer) const
{
    std::for_each(
            segments.begin(), segments.end(),
            std::bind(&Segment::render, std::placeholders::_1, renderer));
}

Snake::Segment::Segment(int x_pos, int y_pos, int width)
    : segment{x_pos, y_pos, width, width} {}

void Snake::Segment::render(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(
            renderer, fill_color.r, fill_color.g, fill_color.b, fill_color.a); 
    SDL_RenderFillRect(renderer, &segment);
    SDL_SetRenderDrawColor(
            renderer, outline_color.r, outline_color.g, outline_color.b,
            outline_color.a); 
    SDL_RenderDrawRect(renderer, &segment);
}
