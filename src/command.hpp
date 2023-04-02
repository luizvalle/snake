#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include "entity.hpp"
#include "component.hpp"

namespace snake_game {
    struct Command {
        virtual ~Command() {};
        virtual void execute() = 0;
    };

    class QuitCommand final : public Command {
        public:
            QuitCommand(bool& game_over) : game_over{game_over} {}
            ~QuitCommand() = default;
            virtual void execute() override { game_over = true; };
        private:
            bool& game_over;
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
}

#endif
