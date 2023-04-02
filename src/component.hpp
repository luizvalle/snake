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
        VelocityComponent(uint16_t speed, Direction direction)
            : speed{speed}, direction{direction} {}
        uint16_t speed;
        Direction direction;
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
            Segment(uint16_t x,
                    uint16_t y,
                    uint16_t w,
                    RectangleRenderComponent::Color color)
                : position_component{x, y}, render_component{w, w, color} {}
            PositionComponent position_component;
            RectangleRenderComponent render_component;
        };
        SnakeComponent(uint16_t x,
                       uint16_t y,
                       uint16_t w,
                       RectangleRenderComponent::Color color,
                       VelocityComponent::Direction direction)
            : velocity_component{w, direction}{
            segments.emplace_back(x, y, w, color);
            segments.emplace_back(x - w, y, w, color);
        };
        std::vector<Segment> segments;
        VelocityComponent velocity_component;
    };
}

#endif
