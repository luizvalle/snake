#include "system.hpp"

#include <cstddef>
#include <vector>

namespace snake_game {
    void RenderSystem::update(EntityManager::EntityIterator start, EntityManager::EntityIterator end) {
        graphics_->clear();
        while (start != end) {
            auto &entity = *start++;
            if (entity.has_component<PositionComponent>() &&
                entity.has_component<GridCellRenderComponent>()) {
                const auto &position = entity.get_component<PositionComponent>();
                const auto &render = entity.get_component<GridCellRenderComponent>();
                graphics_->draw_rectangle(position, render);
            } else if (entity.has_component<SnakeComponent>()) {
                _render_snake(entity);
            }
        }
        graphics_->present();
    }

    void RenderSystem::_render_snake(Entity &entity) {
        const auto &snake_component = entity.get_component<SnakeComponent>();
        for (const auto &segment : snake_component.segments) {
            const auto &position = segment.position_component;
            const auto &render = segment.rectangle_render_component;
            graphics_->draw_rectangle(position, render);
        }
    }

    void MovementSystem::update(EntityManager::EntityIterator start, EntityManager::EntityIterator end) {
        while (start != end) {
            auto &entity = *start++;
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
        int16_t new_x = head.position_component.x;
        int16_t new_y = head.position_component.y;
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
        tail.position_component.x = new_x;
        tail.position_component.y = new_y;
        segments.splice(segments.begin(), segments, --segments.end());
    }

    void CollisionSystem::update(EntityManager::EntityIterator start, EntityManager::EntityIterator end) {
        // std::vector<size_t> snake_ids, apple_ids;
        // for (auto &entity : entity_manager) {
        //     size_t id = entity.id();
        //     if (entity.has_component<SnakeComponent>()) {
        //         snake_ids.push_back(id);
        //     } else {
        //         apple_ids.push_back(id);
        //     }
        // }
        // for (auto snake_id : snake_ids) {
        //     auto &snake_entity = entity_manager.get_entity(snake_id);
        //     auto &head_position =
        //         snake_entity.get_component<SnakeComponent>().segments.front().position_component;
        //     for (auto apple_id : apple_ids) {
        //         auto &apple_entity = entity_manager.get_entity(apple_id);
        //         auto &apple_position = apple_entity.get_component<PositionComponent>();
        //         if (head_position == apple_position) {
        //             entity_manager.add_segment_to_snake(snake_id);
        //             entity_manager.create_apple();
        //             entity_manager.remove_entity(apple_id);
        //         }
        //     }
        // }
    }
} // namespace snake_game
