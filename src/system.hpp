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

    class RenderSystem final : public System {
        public:
            virtual void update(std::vector<Entity>& entities) override;
        private:
            void _render_normal(Entity& entity, SDL_Renderer *renderer);
            void _render_snake(Entity& entity, SDL_Renderer *renderer);
    };
}

#endif
