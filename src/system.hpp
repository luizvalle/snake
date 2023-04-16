#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#include <memory>
#include <vector>

#include "entity.hpp"
#include "entity_manager.hpp"
#include "graphics.hpp"
#include "grid.hpp"

namespace snake_game {
struct System {
  virtual ~System() {}
  virtual void update(EntityManager& entity_manager) = 0;
};

class RenderSystem final : public System {
 public:
  RenderSystem(std::shared_ptr<Graphics> graphics) : graphics_{graphics} {}
  virtual void update(EntityManager& entity_manager) override;

 private:
  void _render_normal(const PositionComponent& position,
                      const GridCellRenderComponent& render);
  void _render_snake(Entity& entity);
  std::shared_ptr<Graphics> graphics_;
};

class MovementSystem : public System {
 public:
  MovementSystem(std::shared_ptr<Grid> grid) : grid_{grid} {}
  virtual void update(EntityManager& entity_manager) override;

 private:
  void _move_snake(Entity& entity);
  std::shared_ptr<Grid> grid_;
};
}  // namespace snake_game

#endif
