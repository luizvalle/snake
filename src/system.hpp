#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#include <memory>
#include <vector>

#include "entity.hpp"
#include "entity_manager.hpp"
#include "graphics.hpp"

namespace snake_game {
struct System {
  virtual void update(EntityManager& entity_manager) = 0;
};

class RenderSystem final : public System {
 public:
  RenderSystem(std::shared_ptr<Graphics> graphics) : m_graphics{graphics} {}
  virtual void update(EntityManager& entity_manager) override;

 private:
  void _render_normal(const PositionComponent& position,
                      const RectangleRenderComponent& render);
  void _render_snake(Entity& entity);
  std::shared_ptr<Graphics> m_graphics;
};

class MovementSystem : public System {
 public:
  virtual void update(EntityManager& entity_manager) override;

 private:
  void _move_snake(Entity& entity);
};
}  // namespace snake_game

#endif
