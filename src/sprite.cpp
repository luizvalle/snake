#include <algorithm>
#include "sprite.hpp"

namespace snake_game {
    bool BoundingBox::intersects(const BoundingBox& other) const {
        bool x_intersect = std::min(m_x + m_w, other.m_x + other.m_w) > std::max(m_x, other.m_x);
        bool y_intersect = std::min(m_y + m_h, other.m_y + other.m_h) > std::max(m_y, other.m_y);
        return x_intersect && y_intersect;
    }
}
