#ifndef __COMPONENTS_HPP__
#define __COMPONENTS_HPP__

#include <cstdint>
#include <list>

namespace snake_game {
struct Component {
  virtual ~Component() {}
};

struct PositionComponent final : public Component {
  PositionComponent(int16_t x, int16_t y) : x{x}, y{y} {}
  int16_t x, y;
};

struct VelocityComponent final : public Component {
  enum class Direction : uint8_t { UP, DOWN, LEFT, RIGHT };
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

struct RectangleShapeComponent : public Component {
  RectangleShapeComponent(uint16_t w, uint16_t h) : w{w}, h{h} {}
  uint16_t w, h;
};

struct RectangleRenderComponent : public Component {
  RectangleRenderComponent(const RectangleShapeComponent& rect,
                           const ColorComponent& fill_color,
                           const ColorComponent& border_color)
      : rect{rect}, fill_color{fill_color}, border_color{border_color} {}
  RectangleShapeComponent rect;
  ColorComponent fill_color;
  ColorComponent border_color;
};

struct RectangleSegmentComponent final : public Component {
  RectangleSegmentComponent(const PositionComponent& position,
                            const RectangleRenderComponent& rect_render)
      : position_component{position}, rectangle_render_component{rect_render} {}
  PositionComponent position_component;
  RectangleRenderComponent rectangle_render_component;
};

struct SnakeComponent final : public Component {
  std::list<RectangleSegmentComponent> segments;
};
}  // namespace snake_game

#endif
