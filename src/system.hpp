#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include "entity.hpp"

namespace snake_game {
    struct System {
        virtual void update(std::vector<Entity>& entities) = 0;
    };

    struct RenderSystem final : public System {
        virtual void update(std::vector<Entity>& entities) override;
    };
}

#endif
