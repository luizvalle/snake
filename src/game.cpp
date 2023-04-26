#include "game.hpp"

#include <SDL2/SDL.h>

#include "command.hpp"

namespace snake_game {
    Game::Game(std::shared_ptr<Graphics> graphics,
               std::unique_ptr<EntityManager> entity_manager,
               std::unique_ptr<InputHandler> input_handler)
        : graphics_{graphics},
          entity_manager_{std::move(entity_manager)},
          input_handler_{std::move(input_handler)} {
        auto &snake = entity_manager_->create_snake(5, 5);
        input_handler_->set_quit_command(std::make_unique<QuitCommand>(game_over_));
        input_handler_->bind_command(SDL_Scancode::SDL_SCANCODE_UP,
                                     std::make_unique<ChangeDirectionCommand>(
                                         snake, VelocityComponent::Direction::UP));
        input_handler_->bind_command(SDL_Scancode::SDL_SCANCODE_DOWN,
                                     std::make_unique<ChangeDirectionCommand>(
                                         snake, VelocityComponent::Direction::DOWN));
        input_handler_->bind_command(SDL_Scancode::SDL_SCANCODE_LEFT,
                                     std::make_unique<ChangeDirectionCommand>(
                                         snake, VelocityComponent::Direction::LEFT));
        input_handler_->bind_command(SDL_Scancode::SDL_SCANCODE_RIGHT,
                                     std::make_unique<ChangeDirectionCommand>(
                                         snake, VelocityComponent::Direction::RIGHT));
    }

    void Game::start() {
        entity_manager_->create_apple();
        while (!game_over_) {
            input_handler_->handle_input();
            for (auto &system : systems_) {
                system->update(*entity_manager_);
            }
            SDL_Delay(5000 / 60);
        }
    }
} // namespace snake_game