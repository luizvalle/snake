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
        RectangleRenderComponent(uint16_t w,
                                 uint16_t h,
                                 Color fill_color,
                                 Color border_color)
            : w{w}, h{h}, fill_color{fill_color}, border_color{border_color} {}
        uint16_t w, h;
        Color fill_color;
        Color border_color;
    };

    struct SnakeComponent final : public Component {
        struct Segment final {
            Segment(uint16_t x,
                    uint16_t y,
                    uint16_t w,
                    RectangleRenderComponent::Color border_color,
                    RectangleRenderComponent::Color fill_color)
                : position_component{x, y},
                  render_component{w, w, border_color, fill_color} {}
            PositionComponent position_component;
            RectangleRenderComponent render_component;
        };
        SnakeComponent(uint16_t x,
                       uint16_t y,
                       uint16_t w,
                       RectangleRenderComponent::Color border_color,
                       RectangleRenderComponent::Color fill_color,
                       VelocityComponent::Direction direction)
            : velocity_component{w, direction}{
            segments.emplace_back(x, y, w, border_color, fill_color);
        };
        std::vector<Segment> segments;
        VelocityComponent velocity_component;
    };
}

#endif
