#include <SDL2/SDL.h>
#include "controller.hpp"

static snake::Action handle_key_press(const SDL_Event& event)
{
    snake::Action action;
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
            action = snake::MOVE_UP;
            break;
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
            action = snake::MOVE_DOWN;
            break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
            action = snake::MOVE_LEFT;
            break;
        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
            action = snake::MOVE_RIGHT;
            break;
        default:
            action = snake::NO_OP;
    }

    return action;
}

snake::Action snake::get_action()
{
    SDL_Event event;
    if (!SDL_PollEvent(&event)) {
        return snake::NO_OP;
    }

    snake::Action action;
    switch (event.type) {
        case SDL_QUIT:
            action = snake::EXIT;
            break;
        case SDL_KEYDOWN:
            action = handle_key_press(event);
            break;
        default:
            action = snake::NO_OP;
    }

    return action;
}
