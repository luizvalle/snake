#ifndef __INPUT_HANDLER_HPP__
#define __INPUT_HANDLER_HPP__

#include <SDL2/SDL.h>

#include <memory>
#include <unordered_map>

#include "command.hpp"

namespace snake_game {
    class InputHandler {
    public:
        InputHandler() : quit_command_{nullptr} {}
        void bind_command(SDL_Scancode key, std::unique_ptr<Command> command) {
            commands_[key] = std::move(command);
        }
        void set_quit_command(std::unique_ptr<Command> command) {
            quit_command_ = std::move(command);
        }
        void handle_input();

    private:
        std::unique_ptr<Command> quit_command_;
        std::unordered_map<SDL_Scancode, std::unique_ptr<Command>> commands_;
    };
} // namespace snake_game

#endif
