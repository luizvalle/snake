#include "input_handler.hpp"

namespace snake_game {
void InputHandler::handle_input() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      if (m_quit_command) {
        m_quit_command->execute();
      }
    } else if (event.type == SDL_KEYDOWN) {
      auto command_it = m_commands.find(event.key.keysym.scancode);
      if (command_it != m_commands.end() && command_it->second) {
        command_it->second->execute();
      }
    }
  }
}
};  // namespace snake_game
