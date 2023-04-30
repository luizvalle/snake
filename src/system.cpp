#include "system.hpp"

#include <cstddef>
#include <vector>

#include <iostream>

namespace snake_game {
    void RenderSystem::update(EntityManager &entity_manager) {
        graphics_->clear();
        for (auto &entity : entity_manager) {
            if (!(entity.has_component<PositionComponent>()
                  && entity.has_component<ColorComponent>())) {
                continue;
            }
            const auto &position = *entity.get_component<PositionComponent>();
            int x = grid_->position_to_pixel(position.x);
            int y = grid_->position_to_pixel(position.y);
            const auto &color = *entity.get_component<ColorComponent>();
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
        auto head_node_ptr = entity.get_component<NodeComponent<Entity>>();
        auto &head_position = *entity.get_component<PositionComponent>();
        const auto &velocity = *entity.get_component<VelocityComponent>();

        auto old_tail_node_ptr = head_node_ptr->prev.lock();
        if (!old_tail_node_ptr) {
            throw std::runtime_error("The old tail node no longer exists.");
        }
        auto old_tail_ptr = old_tail_node_ptr->container.lock();
        if (!old_tail_ptr) {
            throw std::runtime_error("The old tail entity no longer exists.");
        }
        auto &old_tail_position = *old_tail_ptr->get_component<PositionComponent>();

        auto new_tail_node_ptr = old_tail_node_ptr->prev.lock();
        if (!new_tail_node_ptr) {
            throw std::runtime_error("The new tail node no longer exists.");
        }
        auto new_tail_ptr = new_tail_node_ptr->container.lock();
        if (!new_tail_ptr) {
            throw std::runtime_error("The new tail entity no longer exists.");
        }

        old_tail_position = head_position;
        new_tail_node_ptr->next = head_node_ptr;
        old_tail_node_ptr->next = head_node_ptr->next;
        old_tail_node_ptr->prev = head_node_ptr;
        head_node_ptr->next = old_tail_node_ptr;
        head_node_ptr->prev = new_tail_node_ptr;

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
        for (auto it1 = entity_manager.begin(); it1 != entity_manager.end(); ++it1) {
            auto &entity1 = *it1;
            if (!entity1.has_component<PositionComponent>()) {
                continue;
            }
            auto it2 = it1;
            ++it2;
            for (; it2 != entity_manager.end(); ++it2) {
                auto &entity2 = *it2;
                if (entity1 == entity2) {
                    continue;
                }
                if (!entity2.has_component<PositionComponent>()) {
                    continue;
                }
                auto &pos1 = *entity1.get_component<PositionComponent>();
                auto &pos2 = *entity2.get_component<PositionComponent>();
                if (pos1 == pos2) {
                    
                }
            }
        }
    }
} // namespace snake_game
