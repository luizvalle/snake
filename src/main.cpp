#include <SDL2/SDL.h>

#include <memory>
#include <vector>
#include <cstdint>

#include "entity_manager.hpp"
#include "graphics.hpp"
#include "grid.hpp"
#include "input_handler.hpp"
#include "system.hpp"
#include "game.hpp"

using namespace snake_game;

const char *kGameName = "Snake";
constexpr unsigned int kWindowWidth = 800;
constexpr unsigned int kWindowHeight = 800;
constexpr uint16_t kCellSize = 20;

int main(void) {
  auto graphics = std::make_shared<SDLGraphics>();
  graphics->create_window(kGameName, kWindowWidth, kWindowHeight);

  auto grid = std::make_shared<Grid>(kCellSize, kWindowWidth / kCellSize,
  kWindowHeight / kCellSize);
  graphics->add_grid(grid);

  auto render_system = std::make_unique<RenderSystem>(graphics);
  auto movement_system = std::make_unique<MovementSystem>(grid);
  auto collision_system = std::make_unique<CollisionSystem>();

  auto entity_manager = std::make_unique<EntityManager>(grid);
  auto input_handler = std::make_unique<InputHandler>();

  Game game{graphics, std::move(entity_manager), std::move(input_handler)};
  game.add_system(std::move(movement_system));
  game.add_system(std::move(render_system));
  game.add_system(std::move(collision_system));
  game.start();

  return 0;
}
