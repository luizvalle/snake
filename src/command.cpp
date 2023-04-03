#include <stdexcept>
#include "command.hpp"

namespace snake_game {
    ChangeDirectionCommand::ChangeDirectionCommand(Entity& entity,
            VelocityComponent::Direction direction)
        : m_entity{entity}, m_new_direction{direction} {
        if (!m_entity.has_component<VelocityComponent>()) {
            throw std::runtime_error("Missing velocity component.");
        }
    }

    void ChangeDirectionCommand::execute() {
        auto& velocity = m_entity.get_component<VelocityComponent>();
        auto& direction = velocity.direction;
        if (direction == VelocityComponent::Direction::UP
            && m_new_direction == VelocityComponent::Direction::DOWN) {
            return;
        } else if (direction == VelocityComponent::Direction::DOWN
                   && m_new_direction == VelocityComponent::Direction::UP) {
            return;
        } else if (direction == VelocityComponent::Direction::LEFT
                   && m_new_direction == VelocityComponent::Direction::RIGHT) {
            return;
        } else if (direction == VelocityComponent::Direction::RIGHT
                   && m_new_direction == VelocityComponent::Direction::LEFT) {
            return;
        }
        direction = m_new_direction;
    }
}
