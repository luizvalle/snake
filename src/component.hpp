#ifndef __COMPONENTS_HPP__
#define __COMPONENTS_HPP__

#include <cstdint>
#include <list>

namespace snake_game {
    struct Component {
        virtual ~Component() {}
    };

    struct PositionComponent final : public Component {
        PositionComponent(int32_t x, int32_t y) : x{x}, y{y} {}
        bool operator==(const PositionComponent &other) const {
            return (x == other.x) && (y == other.y);
        }
        int32_t x, y;
    };

    struct VelocityComponent final : public Component {
        enum class Direction : uint8_t { UP,
                                         DOWN,
                                         LEFT,
                                         RIGHT };
        VelocityComponent(uint16_t speed, Direction direction)
            : speed{speed}, direction{direction} {}
        uint16_t speed;
        Direction direction;
    };

    struct ColorComponent : public Component {
        ColorComponent(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
            : r{r}, g{b}, b{b}, a{a} {}
        uint8_t r, g, b, a;
    };

    struct GridCellComponent : public Component {
        GridCellComponent(const PositionComponent &position,
                          const ColorComponent &fill_color,
                          const ColorComponent &border_color)
            : position{position}, fill_color{fill_color},
            border_color{border_color} {}
        PositionComponent position;
        ColorComponent fill_color;
        ColorComponent border_color;
    };

    struct SnakeComponent final : public Component {
        std::list<GridCellComponent> segments;
    };
} // namespace snake_game

#endif
