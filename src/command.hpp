#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include "component.hpp"
#include "entity.hpp"

namespace snake_game {
struct Command {
  virtual ~Command(){};
  virtual void execute() = 0;
};

class QuitCommand final : public Command {
 public:
  QuitCommand(bool& quit) : quit_{quit} {}
  ~QuitCommand() = default;
  virtual void execute() override { quit_ = true; };

 private:
  bool& quit_;
};

class ChangeDirectionCommand final : public Command {
 public:
  ChangeDirectionCommand(Entity& entity,
                         VelocityComponent::Direction direction);
  ~ChangeDirectionCommand() = default;
  virtual void execute() override;

 private:
  Entity& entity_;
  VelocityComponent::Direction new_direction_;
};
}  // namespace snake_game

#endif
