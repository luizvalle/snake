#ifndef __COMPONENTS_HPP__
#define __COMPONENTS_HPP__

#include <cstdint>
#include <vector>

namespace snake_game {
    struct Component {
        virtual ~Component() {}
    };

    struct PositionComponent final : public Component {
        PositionComponent(uint16_t x, uint16_t y) : x{x}, y{y} {} 
        uint16_t x, y;
    };

    struct VelocityComponent final : public Component {
        enum class Direction : uint8_t { UP, DOWN, LEFT, RIGHT };
        VelocityComponent(uint8_t speed, Direction direction)
            : speed{speed}, direction{direction} {}
        uint8_t speed;
        Direction direction;
    };

    struct PlayerControlledComponent final : public Component {
        PlayerControlledComponent(bool is_player_controlled)
            : is_player_controlled{is_player_controlled} {}
        bool is_player_controlled;
    };

    struct RectangleRenderComponent final : public Component {
        struct Color {
            uint8_t r, g, b, a;
        };
        RectangleRenderComponent(uint16_t w, uint16_t h, Color color)
            : w{w}, h{h}, color{color} {}
        uint16_t w, h;
        Color color;
    };

    struct SnakeComponent final : public Component {
        struct Segment final {
            PositionComponent position_component;
            RectangleRenderComponent render_component;
        };
        std::vector<Segment> segments;
        PlayerControlledComponent player_controlled_component {true};
        VelocityComponent velocity_component;
    };
}

#endif
