#include <utility>
#include <algorithm>
#include <functional>
#include <SDL2/SDL.h>
#include "snake.hpp"

using namespace snake;

constexpr int SPEED = 300;

Snake::Snake(int x_pos, int y_pos, size_t length)
{
    while (length--) {
        Snake::Segment segment {x_pos, y_pos};
        segments.push_front(std::move(segment));
        x_pos -= segment.get_length();
    }
}

void Snake::change_direction(Direction direction)
{
    switch (direction) {
        case UP:
            x_vel = 0;
            y_vel = -SPEED;
            break;
        case DOWN:
            x_vel = 0;
            y_vel = SPEED;
            break;
        case LEFT:
            x_vel = -SPEED;
            y_vel = 0;
            break;
        case RIGHT:
            x_vel = SPEED;
            y_vel = 0;
            break;
    }
}

void Snake::move()
{
    auto head = segments.begin();
    int prev_x = head->get_x(), prev_y = head->get_y();
    head->set_x(static_cast<int>(prev_x + x_vel / 60));
    head->set_y(static_cast<int>(prev_y + y_vel / 60));
    for (auto curr = ++segments.begin(); curr != segments.end(); curr++) {
        int tmp_x = curr->get_x(), tmp_y = curr->get_y();
        curr->set_x(prev_x);
        curr->set_y(prev_y);
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
