#include "entity_manager.hpp"

#include "component.hpp"

namespace snake_game {
Entity &EntityManager::create_entity(EntityManager::EntityType type, int16_t x,
                                     int16_t y) {
  Entity *entity_ptr;
  size_t id = next_id_++;
  switch (type) {
    case EntityManager::EntityType::SNAKE:
      entity_ptr = _create_snake(id, x, y);
      break;
    case EntityManager::EntityType::APPLE:
      entity_ptr = _create_apple(id, x, y);
      break;
  }
  entities_.emplace(id, entity_ptr);
  return *entity_ptr;
}

Entity *EntityManager::_create_snake(size_t id, int16_t x, int16_t y) {
  Entity *entity_ptr = new Entity(id);
  entity_ptr->add_component<SnakeComponent>();
  entity_ptr->add_component<VelocityComponent>(
      1, VelocityComponent::Direction::RIGHT);

  PositionComponent position{x, y};
  ColorComponent fill_color{0, 71, 100, 255};
  ColorComponent border_color{0, 0, 0, 255};
  GridCellRenderComponent rect_render{fill_color, border_color};
  entity_ptr->get_component<SnakeComponent>().segments.emplace_back(
      position, rect_render);
  return entity_ptr;
}

Entity *EntityManager::_create_apple(size_t id, int16_t x, int16_t y) {
  PositionComponent position{x, y};
  ColorComponent fill_color{195, 55, 47, 255};
  ColorComponent border_color{0, 0, 0, 255};
  Entity *entity_ptr = new Entity(id);
  entity_ptr->add_component<GridCellRenderComponent>(fill_color, border_color);
  return entity_ptr;
}
}  // namespace snake_game
