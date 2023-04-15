#include "command.hpp"

#include <stdexcept>

namespace snake_game {
ChangeDirectionCommand::ChangeDirectionCommand(
    Entity& entity, VelocityComponent::Direction direction)
    : entity_{entity}, new_direction_{direction} {
  if (!entity_.has_component<VelocityComponent>()) {
    throw std::runtime_error("Missing velocity component.");
  }
}

void ChangeDirectionCommand::execute() {
  auto& velocity = entity_.get_component<VelocityComponent>();
  auto& direction = velocity.direction;
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
}  // namespace snake_game
