#include <utility>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "snake.hpp"

namespace snake_game {
    Snake::Snake(int x_pos, int y_pos, size_t length, int w)
        : m_width{w}, m_speed{w} {
        if (length < 1) {
            throw new std::invalid_argument(
                    "The length of the snake must be at least 1.");
        }
        while (length--) {
            Snake::Segment segment {x_pos, y_pos, m_width};
            m_segments.push_back(std::move(segment));
            x_pos -= m_width;
        }
    }

    void Snake::change_direction(Direction direction) {
        switch (direction) {
            case UP:
                m_x_vel = 0;
                m_y_vel = -m_speed;
                break;
            case DOWN:
                m_x_vel = 0;
                m_y_vel = m_speed;
                break;
            case LEFT:
                m_x_vel = -m_speed;
                m_y_vel = 0;
                break;
            case RIGHT:
                m_x_vel = m_speed;
                m_y_vel = 0;
                break;
        }
    }

    void Snake::move() {
        auto segment = m_segments.begin();
        int prev_x = segment->get_x(), prev_y = segment->get_y();
        segment->set_x(prev_x + m_x_vel);
        segment->set_y(prev_y + m_y_vel);
        while (++segment != m_segments.end()) {
            int tmp_x = segment->get_x(), tmp_y = segment->get_y();
            segment->set_x(prev_x);
            segment->set_y(prev_y);
            prev_x = tmp_x;
            prev_y = tmp_y;
        }
    }

    bool Snake::self_collided() const {
        auto segment = m_segments.begin();
        auto head_bounding_box = segment->get_bounding_box();
        if (++segment == m_segments.end()) { // Skip second segment
            return false;
        }
        while (++segment != m_segments.end()) {
            auto bounding_box = segment->get_bounding_box();
            if (head_bounding_box.intersects(bounding_box)) {
                return true;
            }
        }
        return false;
    }

    void Snake::render(SDL_Renderer *renderer) const {
        std::for_each(m_segments.begin(),
                      m_segments.end(),
                      std::bind(&Segment::render,
                                std::placeholders::_1,
                                renderer));
    }

    void Snake::Segment::render(SDL_Renderer *renderer) const {
        SDL_SetRenderDrawColor(renderer,
                m_fill_color.r,
                m_fill_color.g,
                m_fill_color.b,
                m_fill_color.a);
        SDL_RenderFillRect(renderer, &m_segment);
        SDL_SetRenderDrawColor(renderer,
                m_outline_color.r,
                m_outline_color.g,
                m_outline_color.b,
                m_outline_color.a);
        SDL_RenderDrawRect(renderer, &m_segment);
    }
}
