#include "system.hpp"

#include <stdexcept>

namespace snake_game {
void RenderSystem::update(EntityManager& entity_manager) {
  graphics_->clear();
  for (auto& entity : entity_manager) {
    if (entity.has_component<PositionComponent>() &&
        entity.has_component<RectangleRenderComponent>()) {
      const auto& position = entity.get_component<PositionComponent>();
      const auto& render = entity.get_component<RectangleRenderComponent>();
      graphics_->draw_rectangle(position, render);
    } else if (entity.has_component<SnakeComponent>()) {
      _render_snake(entity);
    }
  }
  graphics_->present();
}

void RenderSystem::_render_snake(Entity& entity) {
  const auto& snake_component = entity.get_component<SnakeComponent>();
  for (const auto& segment : snake_component.segments) {
    const auto& position = segment.position_component;
    const auto& render = segment.rectangle_render_component;
    graphics_->draw_rectangle(position, render);
  }
}

void MovementSystem::update(EntityManager& entity_manager) {
  for (auto& entity : entity_manager) {
    if (entity.has_component<SnakeComponent>() &&
        entity.has_component<VelocityComponent>()) {
      _move_snake(entity);
    }
  }
}

void MovementSystem::_move_snake(Entity& entity) {
  auto& segments = entity.get_component<SnakeComponent>().segments;
  const auto& velocity_component = entity.get_component<VelocityComponent>();
  const auto& head = segments.front();
  int16_t new_x = head.position_component.x;
  int16_t new_y = head.position_component.y;
  switch (velocity_component.direction) {
    case VelocityComponent::Direction::UP:
      new_y -= velocity_component.speed;
      break;
    case VelocityComponent::Direction::DOWN:
      new_y += velocity_component.speed;
      break;
    case VelocityComponent::Direction::LEFT:
      new_x -= velocity_component.speed;
      break;
    case VelocityComponent::Direction::RIGHT:
      new_x += velocity_component.speed;
      break;
  }
  auto& tail = segments.back();
  tail.position_component.x = new_x;
  tail.position_component.y = new_y;
  segments.splice(segments.begin(), segments, --segments.end());
}
}  // namespace snake_game
