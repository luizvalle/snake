#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include "component.hpp"
#include "entity.hpp"

#include <memory>

namespace snake_game {
    struct Command {
        virtual ~Command(){};
        virtual void execute() = 0;
    };

    class QuitCommand final : public Command {
    public:
        QuitCommand(bool &quit) : quit_{quit} {}
        virtual void execute() override { quit_ = true; };

    private:
        bool &quit_;
    };

    class ChangeDirectionCommand final : public Command {
    public:
        ChangeDirectionCommand(std::weak_ptr<Entity> entity_ptr,
                               VelocityComponent::Direction direction);
        virtual void execute() override;

    private:
        std::weak_ptr<Entity> entity_ptr_;
        VelocityComponent::Direction new_direction_;
    };
} // namespace snake_game

#endif
