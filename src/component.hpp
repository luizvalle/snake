#ifndef __COMPONENTS_HPP__
#define __COMPONENTS_HPP__

#include <cstdint>

namespace snake_game {

    struct Component {
        virtual ~Component() {}
    };

    struct PositionComponent : Component {
        PositionComponent(uint16_t x, uint16_t y) : x{x}, y{y} {} 
        uint16_t x, y;
    };


    struct VelocityComponent : Component {
        enum class Direction : uint8_t { UP, DOWN, LEFT, RIGHT };
        VelocityComponent(uint8_t speed, Direction direction)
            : speed{speed}, direction{direction} {}
        const uint8_t speed;
        Direction direction;
    };

    struct PlayerControlledComponent {
        bool is_player_controlled;
    };


    struct RectangleRenderComponent : Component {
        struct Rect {
            uint16_t x, y, w, h;
        };
        struct Color {
            uint8_t r, g, b, a;
        };
        RectangleRenderComponent(Rect rect, Color color)
            : rect{rect}, color{color} {}
        Rect rect;
        Color color;
    };
}

#endif
