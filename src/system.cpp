#include "system.hpp"

#include <cstddef>
#include <vector>

namespace snake_game {
    void RenderSystem::update(EntityManager &entity_manager) {
        graphics_->clear();
        for (auto &entity : entity_manager) {
            if (entity.has_component<GridCellComponent>()) {
                _render_normal(entity.get_component<GridCellComponent>());
            } else if (entity.has_component<SnakeComponent>()) {
                _render_snake(entity.get_component<SnakeComponent>());
            }
        }
        graphics_->present();
    }

    void RenderSystem::_render_normal(const GridCellComponent &cell) {
        const auto &position = cell.position;
        int x = grid_->position_to_pixel(position.x);
        int y = grid_->position_to_pixel(position.y);
        const auto &border_color = cell.border_color;
        const auto &fill_color = cell.fill_color;
        graphics_->draw_rectangle(x, y, grid_->cell_size(), grid_->cell_size(),
                                  border_color.r, border_color.g,
                                  border_color.b, border_color.a);
        graphics_->fill_rectangle(x, y, grid_->cell_size(), grid_->cell_size(),
                                  fill_color.r, fill_color.g, fill_color.b,
                                  fill_color.a);
    }

    void RenderSystem::_render_snake(const SnakeComponent &snake) {
        for (const auto &segment : snake.segments) {
            _render_normal(segment);
        }
    }

    void MovementSystem::update(EntityManager &entity_manager) {
        for (auto &entity : entity_manager) {
            if (entity.has_component<SnakeComponent>() &&
                entity.has_component<VelocityComponent>()) {
                _move_snake(entity);
            }
        }
    }

    void MovementSystem::_move_snake(Entity &entity) {
        auto &segments = entity.get_component<SnakeComponent>().segments;
        const auto &velocity_component = entity.get_component<VelocityComponent>();
        const auto &head = segments.front();
        int16_t new_x = head.position.x;
        int16_t new_y = head.position.y;
        uint16_t speed = velocity_component.speed;
        switch (velocity_component.direction) {
        case VelocityComponent::Direction::UP:
            new_y -= speed;
            break;
        case VelocityComponent::Direction::DOWN:
            new_y += speed;
            break;
        case VelocityComponent::Direction::LEFT:
            new_x -= speed;
            break;
        case VelocityComponent::Direction::RIGHT:
            new_x += speed;
            break;
        }
        auto &tail = segments.back();
        tail.position.x = new_x;
        tail.position.y = new_y;
        segments.splice(segments.begin(), segments, --segments.end());
    }

    void CollisionDetectionSystem::update(EntityManager &entity_manager) {
        std::vector<size_t> snake_ids, apple_ids;
        for (auto &entity : entity_manager) {
            size_t id = entity.id();
            if (entity.has_component<SnakeComponent>()) {
                snake_ids.push_back(id);
            } else if (entity.has_component<GridCellComponent>()) {
                apple_ids.push_back(id);
            }
        }
        for (auto snake_id : snake_ids) {
            auto &snake_entity = entity_manager.get_entity(snake_id);
            const auto &head_position =
                snake_entity.get_component<SnakeComponent>().segments.front().position;
            for (auto apple_id : apple_ids) {
                auto &apple_entity = entity_manager.get_entity(apple_id);
                const auto &cell = apple_entity.get_component<GridCellComponent>();
                auto &apple_position = cell.position;
                if (head_position == apple_position) { // Snake ate apple
                }
            }
        }
    }
} // namespace snake_game
