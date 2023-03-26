#include <utility>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "snake.hpp"

static inline int _sign(int a) {
    return (a > 0) - (a < 0);
}

static inline bool _is_reverse(int a, int b) {
    return (_sign(a) + _sign(b)) == 0;
}

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
        int new_x_vel, new_y_vel;
        switch (direction) {
            case UP:
                new_x_vel = 0;
                new_y_vel = -m_speed;
                break;
            case DOWN:
                new_x_vel = 0;
                new_y_vel = m_speed;
                break;
            case LEFT:
                new_x_vel = -m_speed;
                new_y_vel = 0;
                break;
            case RIGHT:
                new_x_vel = m_speed;
                new_y_vel = 0;
                break;
        }
        if (_is_reverse(new_x_vel, m_x_vel)
            && _is_reverse(new_y_vel, m_y_vel)) {
            return; // Not allow snake to go back on itself
        }
        m_x_vel = new_x_vel;
        m_y_vel = new_y_vel;
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

    void Snake::add_segment() {
        auto segment = --m_segments.end();
        const Segment& tail = *segment;
        int new_x, new_y;
        if (segment-- == m_segments.begin()) { // Only one segment
            new_x = tail.get_x() - m_x_vel;
            new_y = tail.get_y() - m_y_vel;
        } else {
            const Segment& before_tail = *segment;
            int x_diff = before_tail.get_x() - tail.get_x();
            int y_diff = before_tail.get_y() - tail.get_y();
            new_x = tail.get_x() + x_diff;
            new_y = tail.get_y() + y_diff;
        }
        Segment new_segment {new_x, new_y, m_width};
        m_segments.push_back(std::move(new_segment));
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
        SDL_RenderFillRect(renderer, &m_bounding_box);
        SDL_SetRenderDrawColor(renderer,
                m_outline_color.r,
                m_outline_color.g,
                m_outline_color.b,
                m_outline_color.a);
        SDL_RenderDrawRect(renderer, &m_bounding_box);
    }
}
