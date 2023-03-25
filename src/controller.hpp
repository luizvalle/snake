#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

#include <SDL2/SDL.h>

namespace snake_game {
    enum Action { NO_OP, EXIT, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

    Action get_action();
}

#endif
