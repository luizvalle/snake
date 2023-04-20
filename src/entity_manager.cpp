#include "entity_manager.hpp"

#include <vector>

#include "component.hpp"

namespace snake_game {
Entity& EntityManager::create_snake(int16_t x, int16_t y) {
  size_t id = next_id_++;
  Entity* entity_ptr = new Entity(id);
  entity_ptr->add_component<SnakeComponent>();
  entity_ptr->add_component<VelocityComponent>(
      1, VelocityComponent::Direction::RIGHT);

  PositionComponent position{x, y};
  ColorComponent fill_color{0, 71, 100, 255};
  ColorComponent border_color{0, 0, 0, 255};
  GridCellRenderComponent rect_render{fill_color, border_color};
  entity_ptr->get_component<SnakeComponent>().segments.emplace_back(
      position, rect_render);
  entities_.emplace(id, entity_ptr);
  return *entity_ptr;
}

Entity& EntityManager::create_apple() {
  size_t id = next_id_++;
  Entity* entity_ptr = new Entity(id);
  auto [x, y] = _get_random_empty_position();
  entity_ptr->add_component<PositionComponent>(x, y);
  ColorComponent fill_color{195, 55, 47, 255};
  ColorComponent border_color{0, 0, 0, 255};
  entity_ptr->add_component<GridCellRenderComponent>(fill_color, border_color);
  entities_.emplace(id, entity_ptr);
  return *entity_ptr;
}

std::pair<int32_t, int32_t> EntityManager::_get_random_empty_position() {
  uint16_t num_rows = grid_->num_rows(), num_cols = grid_->num_cols();
  std::vector<std::vector<bool>> occupied_cells(num_rows,
                                       std::vector<bool>(num_cols, false));
  for (auto& entity : *this) {
    if (!entity.has_component<PositionComponent>()) {
      continue;
    }
    auto& position = entity.get_component<PositionComponent>();
    if (position.x < 0 || position.y < 0 || position.x >= num_rows
        || position.y >= num_cols) {
      continue;
    }
    occupied_cells[position.x][position.y] = true;
  }
  std::vector<std::pair<int32_t, int32_t>> free_positions;
  for (size_t row = 0; row < num_rows; row++) {
    for (size_t col = 0; col < num_cols; col++) {
      if (!occupied_cells[row][col]) {
        free_positions.emplace_back(row, col);
      }
    }
  }
  size_t i = std::uniform_int_distribution<size_t>{
      0, free_positions.size()}(random_number_generator_);
  return free_positions[i];
}

void EntityManager::add_segment_to_snake(size_t entity_id) {
    auto& snake = get_entity(entity_id);
    if (!snake.has_component<SnakeComponent>()) {
      throw std::runtime_error("Not a snake.");
    }
    auto& segments = snake.get_component<SnakeComponent>().segments;
    auto& tail = segments.back();

    PositionComponent position = tail.position_component;
    ColorComponent fill_color{0, 71, 100, 255};
    ColorComponent border_color{0, 0, 0, 255};
    GridCellRenderComponent rect_render{fill_color, border_color};
    segments.emplace_back(position, rect_render);
}
}  // namespace snake_game
