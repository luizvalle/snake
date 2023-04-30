#include "command.hpp"

#include <stdexcept>

namespace snake_game {
    ChangeDirectionCommand::ChangeDirectionCommand(
        std::weak_ptr<Entity> entity_ptr, VelocityComponent::Direction direction)
        : entity_ptr_{entity_ptr}, new_direction_{direction} {
        auto ptr = entity_ptr_.lock();
        if (!ptr) {
            throw std::runtime_error("The entity was deleted.");
        }
        if (!ptr->has_component<VelocityComponent>()) {
            throw std::runtime_error("Missing velocity component.");
        }
    }

    void ChangeDirectionCommand::execute() {
        auto entity_ptr = entity_ptr_.lock();
        if (!entity_ptr) {
            throw std::runtime_error("The entity was deleted");
        }
        auto &velocity = *entity_ptr->get_component<VelocityComponent>();
        auto &direction = velocity.direction;
        if (direction == VelocityComponent::Direction::UP &&
            new_direction_ == VelocityComponent::Direction::DOWN) {
            return;
        } else if (direction == VelocityComponent::Direction::DOWN &&
                   new_direction_ == VelocityComponent::Direction::UP) {
            return;
        } else if (direction == VelocityComponent::Direction::LEFT &&
                   new_direction_ == VelocityComponent::Direction::RIGHT) {
            return;
        } else if (direction == VelocityComponent::Direction::RIGHT &&
                   new_direction_ == VelocityComponent::Direction::LEFT) {
            return;
        }
        direction = new_direction_;
    }
} // namespace snake_game
