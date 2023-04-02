#ifndef __INPUT_HANDLER_HPP__
#define __INPUT_HANDLER_HPP__

#include <memory>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "command.hpp"

namespace snake_game {
    class InputHandler {
        public:
            InputHandler() : m_quit_command{nullptr} {}
            void bind_command(SDL_Scancode key,
                              std::unique_ptr<Command> command) {
                m_commands[key] = std::move(command);
            }
            void set_quit_command(std::unique_ptr<Command> command) {
                m_quit_command = std::move(command);
            }
            void handle_input();
        private:
            std::unique_ptr<Command> m_quit_command;
            std::unordered_map<SDL_Scancode, std::unique_ptr<Command>> m_commands;
    };
}

#endif
