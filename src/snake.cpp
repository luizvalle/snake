#include <utility>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "snake.hpp"

namespace snake_game {
    static inline bool _is_opposite_direction(Direction d1, Direction d2) {
        return (d1 == UP && d2 == DOWN) || (d1 == DOWN && d2 == UP)
               || (d1 == LEFT && d2 == RIGHT) || (d1 == RIGHT && d2 == LEFT);
    }

    Snake::Snake(int x, int y, size_t length, size_t width)
        : m_width{width} {
        if (length < 1) {
            throw new std::invalid_argument(
                    "The length of the snake must be at least 1.");
        }
        if (width < 1) {
            throw new std::invalid_argument(
                    "The width of the snake must be at least 1.");
        }
        while (length--) {
            m_segments.emplace_back(x, y, m_width);
            x -= m_width;
        }
    }

    void Snake::set_direction(Direction new_direction) {
        if (_is_opposite_direction(direction, new_direction)) {
            return;
        }
        direction = new_direction;
    }

    void Snake::move() {
        const auto& head = m_segments.front();
        int new_x = head.get_x(), new_y = head.get_y();
        switch (direction) {
            case STOPPED:
                return;
            case UP:
                new_y -= m_width;
                break;
            case DOWN:
                new_y += m_width;
                break;
            case LEFT:
                new_x -= m_width;
                break;
            case RIGHT:
                new_x += m_width;
                break;
        }
        auto tail_ptr = --m_segments.end();
        tail_ptr->set_x(new_x);
        tail_ptr->set_y(new_y);
        m_segments.splice(m_segments.begin(), m_segments, tail_ptr);
    }

    bool Snake::self_collided() const {
        if (m_segments.size() < 4) {
            return false;
        }
        auto segment_ptr = m_segments.begin();
        auto head_bounding_box = (segment_ptr++)->get_bounding_box();
        ++segment_ptr; // Skip second segment
        for (; segment_ptr != m_segments.end(); ++segment_ptr) {
            auto bounding_box = segment_ptr->get_bounding_box();
            if (head_bounding_box.intersects(bounding_box)) {
                return true;
            }
        }
        return false;
    }

    void Snake::add_segment() {
        const auto& tail = m_segments.back();
        m_segments.emplace_back(tail.get_x(), tail.get_y(), m_width);
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
