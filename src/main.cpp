#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "entity_manager.hpp"
#include "graphics.hpp"
#include "input_handler.hpp"
#include "system.hpp"
#include "game.hpp"

using namespace snake_game;

int main(void) {
  auto entity_manager = std::make_unique<EntityManager>();
  auto graphics = std::make_shared<SDLGraphics>();
  auto render_system = std::make_unique<RenderSystem>(graphics);
  auto movement_system = std::make_unique<MovementSystem>();
  auto input_handler = std::make_unique<InputHandler>();

  Game game{graphics, std::move(entity_manager), std::move(input_handler)};
  game.add_system(std::move(render_system));
  game.add_system(std::move(movement_system));
  game.start();

  return 0;
}
