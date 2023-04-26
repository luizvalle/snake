#include "input_handler.hpp"

namespace snake_game {
    void InputHandler::handle_input() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                if (quit_command_) {
                    quit_command_->execute();
                }
            } else if (event.type == SDL_KEYDOWN) {
                auto command_it = commands_.find(event.key.keysym.scancode);
                if (command_it != commands_.end() && command_it->second) {
                    command_it->second->execute();
                }
            }
        }
    }
}; // namespace snake_game
