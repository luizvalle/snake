#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include "component.hpp"
#include "entity.hpp"

namespace snake_game {
struct Command {
  virtual ~Command() {};
  virtual void execute() = 0;
};

class QuitCommand final : public Command {
 public:
  QuitCommand(bool& quit) : quit{quit} {}
  ~QuitCommand() = default;
  virtual void execute() override { quit = true; };

 private:
  bool& quit;
};

class ChangeDirectionCommand final : public Command {
 public:
  ChangeDirectionCommand(Entity& entity,
                         VelocityComponent::Direction direction);
  ~ChangeDirectionCommand() = default;
  virtual void execute() override;

 protected:
  Entity& m_entity;
  VelocityComponent::Direction m_new_direction;
};
}  // namespace snake_game

#endif
