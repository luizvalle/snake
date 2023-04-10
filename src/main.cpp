#include <SDL2/SDL.h>

#include <iostream>
#include <vector>

#include "command.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "graphics.hpp"
#include "input_handler.hpp"
#include "system.hpp"

using namespace snake_game;

int main(void) {
  EntityManager entity_manager;
  auto& snake = entity_manager.create_entity(EntityManager::EntityType::SNAKE,
                                             100, 100, 20);

  std::shared_ptr<SDLGraphics> graphics = std::make_shared<SDLGraphics>();
  graphics->create_window("Snake", 400, 400);
  RenderSystem render_system{graphics};
  MovementSystem movement_system;

  bool game_over = false;

  InputHandler input_handler;
  input_handler.set_quit_command(std::make_unique<QuitCommand>(game_over));
  input_handler.bind_command(SDL_Scancode::SDL_SCANCODE_UP,
                             std::make_unique<ChangeDirectionCommand>(
                                 snake, VelocityComponent::Direction::UP));
  input_handler.bind_command(SDL_Scancode::SDL_SCANCODE_DOWN,
                             std::make_unique<ChangeDirectionCommand>(
                                 snake, VelocityComponent::Direction::DOWN));
  input_handler.bind_command(SDL_Scancode::SDL_SCANCODE_LEFT,
                             std::make_unique<ChangeDirectionCommand>(
                                 snake, VelocityComponent::Direction::LEFT));
  input_handler.bind_command(SDL_Scancode::SDL_SCANCODE_RIGHT,
                             std::make_unique<ChangeDirectionCommand>(
                                 snake, VelocityComponent::Direction::RIGHT));

  while (!game_over) {
    input_handler.handle_input();
    movement_system.update(entity_manager);
    render_system.update(entity_manager);
    SDL_Delay(10000 / 60);
  }

  return 0;
}
