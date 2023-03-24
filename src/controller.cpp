#include <SDL2/SDL.h>
#include "controller.hpp"

namespace snake {
    static Action _handle_key_press(const SDL_Event& event) {
        Action action;
        switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                action = MOVE_UP;
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                action = MOVE_DOWN;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                action = MOVE_LEFT;
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                action = MOVE_RIGHT;
                break;
            default:
                action = NO_OP;
        }

        return action;
    }

    Action get_action() {
        SDL_Event event;
        if (!SDL_PollEvent(&event)) {
            return NO_OP;
        }

        Action action;
        switch (event.type) {
            case SDL_QUIT:
                action = EXIT;
                break;
            case SDL_KEYDOWN:
                action = _handle_key_press(event);
                break;
            default:
                action = NO_OP;
        }

        return action;
    }
}
