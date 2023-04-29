#include "entity_manager.hpp"

#include <vector>

#include "component.hpp"

namespace snake_game {
    Entity &EntityManager::create_snake(int32_t x, int32_t y) {
        auto &entity = _create_snake_segment(x, y);
        entity.add_component<VelocityComponent>(
            1, VelocityComponent::Direction::RIGHT);
        entity.add_component<SnakeHeadTagComponent>();
        return entity;
    }

    Entity &EntityManager::_create_snake_segment(int32_t x, int32_t y) {
        size_t id = next_id_++;
        Entity *entity_ptr = new Entity(id);
        entity_ptr->add_component<PositionComponent>(x, y);
        entity_ptr->add_component<ColorComponent>(0, 71, 100, 255);
        entity_ptr->add_component<NodeComponent<Entity>>(entity_ptr);
        entities_.emplace(id, entity_ptr);
        return *entity_ptr;
    }

    Entity &EntityManager::create_apple() {
        size_t id = next_id_++;
        Entity *entity_ptr = new Entity(id);
        auto [x, y] = _get_random_empty_position();
        entity_ptr->add_component<PositionComponent>(x, y);
        entity_ptr->add_component<ColorComponent>(195, 55, 47, 255);
        entities_.emplace(id, entity_ptr);
        return *entity_ptr;
    }

    std::pair<int32_t, int32_t> EntityManager::_get_random_empty_position() {
        uint16_t num_rows = grid_->num_rows(), num_cols = grid_->num_cols();
        std::vector<std::vector<bool>> occupied_cells(num_rows,
                                                      std::vector<bool>(num_cols, false));
        for (auto &entity : *this) {
            if (entity.has_component<PositionComponent>()) {
                const auto &position = entity.get_component<PositionComponent>();
                if (position.x < 0 || position.y < 0 || position.x >= num_rows || position.y >= num_cols) {
                    continue;
                }
                occupied_cells[position.x][position.y] = true;
            }
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
        auto &entity = get_entity(entity_id);
        if (!(entity.has_component<SnakeHeadTagComponent>()
              && entity.has_component<NodeComponent<Entity>>())) {
            throw std::runtime_error("Cannot add segment to non-snake head.");
        }
        auto &head_node = entity.get_component<NodeComponent<Entity>>();
        auto &old_tail = *(head_node.prev->container);
        auto &old_tail_node = old_tail.get_component<NodeComponent<Entity>>();
        auto &old_tail_pos = old_tail.get_component<PositionComponent>();
        auto &new_tail = _create_snake_segment(old_tail_pos.x, old_tail_pos.y);
        auto &new_tail_node = new_tail.get_component<NodeComponent<Entity>>();
        old_tail_node.next = &new_tail_node;
        new_tail_node.prev = &old_tail_node;
        new_tail_node.next = &head_node;
        head_node.prev = &new_tail_node;
    }
} // namespace snake_game
