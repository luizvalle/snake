#include <algorithm>
#include "sprite.hpp"

namespace snake_game {
    bool BoundingBox::intersects(const BoundingBox& other) const {
        bool x_intersect = std::min(x + w, other.x + other.w) > std::max(x, other.x);
        bool y_intersect = std::min(y + h, other.y + other.h) > std::max(y, other.y);
        return x_intersect && y_intersect;
    }
}
