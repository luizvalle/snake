#ifndef __COMPONENTS_HPP__
#define __COMPONENTS_HPP__

#include <cstdint>
#include <memory>

namespace snake_game {
    struct Component {
        virtual ~Component() {}
    };

    struct PositionComponent final : public Component {
        PositionComponent(int32_t x, int32_t y) : x{x}, y{y} {}
        bool operator==(const PositionComponent &other) const {
            return (x == other.x) && (y == other.y);
        }
        PositionComponent &operator=(PositionComponent &other) {
            x = other.x;
            y = other.y;
            return *this;
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

    template <typename T>
    struct NodeComponent final : public Component {
        NodeComponent(std::weak_ptr<T> container) : container{container} {}
        std::weak_ptr<T> container;
        std::weak_ptr<NodeComponent<T>> prev, next;
    };

    struct SnakeHeadTagComponent final : Component {};

    struct AppleTagComponent final : Component {};

    template <typename T>
    struct EntityToEntityCollisionComponent final : Component {
        EntityToEntityCollisionComponent(std::weak_ptr<T> entity1,
                                         std::weak_ptr<T> entity2)
            : entity1{entity1}, entity2{entity2} {}
        std::weak_ptr<T> entity1, entity2;
    };

    struct ToRemoveTagComponent final : Component {};
} // namespace snake_game

#endif
