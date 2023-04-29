#include "system.hpp"

#include <cstddef>
#include <vector>

namespace snake_game {
    void RenderSystem::update(EntityManager &entity_manager) {
        graphics_->clear();
        for (auto &entity : entity_manager) {
            if (!(entity.has_component<PositionComponent>()
                  && entity.has_component<ColorComponent>())) {
                continue;
            }
            const auto &position = entity.get_component<PositionComponent>();
            int x = grid_->position_to_pixel(position.x);
            int y = grid_->position_to_pixel(position.y);
            const auto &color = entity.get_component<ColorComponent>();
            graphics_->draw_rectangle(x, y, grid_->cell_size(),
                                      grid_->cell_size(), 0, 0, 0, 255);
            graphics_->fill_rectangle(x, y, grid_->cell_size(),
                                      grid_->cell_size(), color.r, color.g,
                                      color.b, color.a);
        }
        graphics_->present();
    }

    void MovementSystem::update(EntityManager &entity_manager) {
        for (auto &entity : entity_manager) {
            if (entity.has_component<SnakeHeadTagComponent>()
                && entity.has_component<PositionComponent>()
                && entity.has_component<NodeComponent<Entity>>()
                && entity.has_component<VelocityComponent>()) {
                _move_snake(entity);
            }
        }
    }

    void MovementSystem::_move_snake(Entity &entity) {
        auto &head_node = entity.get_component<NodeComponent<Entity>>();
        auto &head_position = entity.get_component<PositionComponent>();
        const auto &velocity = entity.get_component<VelocityComponent>();
        auto &old_tail = *(head_node.prev->container);
        auto &old_tail_node = old_tail.get_component<NodeComponent<Entity>>();
        auto &old_tail_position = old_tail.get_component<PositionComponent>();
        auto &new_tail = *(old_tail_node.prev->container);
        auto &new_tail_node = new_tail.get_component<NodeComponent<Entity>>();

        old_tail_position = head_position;
        new_tail_node.next = &head_node;
        old_tail_node.next = head_node.next;
        old_tail_node.prev = &head_node;
        head_node.next = &old_tail_node;
        head_node.prev = &new_tail_node;

        int16_t new_x = head_position.x;
        int16_t new_y = head_position.y;
        uint16_t speed = velocity.speed;
        switch (velocity.direction) {
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
        head_position.x = new_x;
        head_position.y = new_y;
    }

    void CollisionDetectionSystem::update(EntityManager &entity_manager) {
        // std::vector<size_t> snake_ids, apple_ids;
        // for (auto &entity : entity_manager) {
        //     size_t id = entity.id();
        //     if (entity.has_component<SnakeComponent>()) {
        //         snake_ids.push_back(id);
        //     } else if (entity.has_component<GridCellComponent>()) {
        //         apple_ids.push_back(id);
        //     }
        // }
        // for (auto snake_id : snake_ids) {
        //     const auto &snake_entity = entity_manager.get_entity(snake_id);
        //     const auto &head_position =
        //         snake_entity.get_component<SnakeComponent>().segments.front().position;
        //     for (auto apple_id : apple_ids) {
        //         auto &apple_entity = entity_manager.get_entity(apple_id);
        //         const auto &cell = apple_entity.get_component<GridCellComponent>();
        //         auto &apple_position = apple_entity.get_component<GridCellComponent>();
        //         if (head_position == apple_position) { // Snake ate apple
        //         }
        //     }
        // }
    }
} // namespace snake_game
