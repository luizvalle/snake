#include <stdexcept>
#include <iostream>
#include <SDL2/SDL.h>
#include "system.hpp"
#include "renderer.hpp"

namespace snake_game {
    void RenderSystem::update(std::vector<Entity>& entities) {
        SDL_Renderer *renderer = Renderer::get_instance().get();
        SDL_RenderClear(renderer);
        for (auto& entity : entities) {
            std::cout << entity.has_component<PositionComponent>() << '\n';
            if (entity.has_component<PositionComponent>()
                && entity.has_component<RectangleRenderComponent>()) {
                auto& position = entity.get_component<PositionComponent>();
                auto& render = entity.get_component<RectangleRenderComponent>();
                SDL_Rect rect {position.x, position.y, render.w, render.h};
                SDL_SetRenderDrawColor(renderer,
                                       render.color.r,
                                       render.color.g,
                                       render.color.b,
                                       render.color.a);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
        }
        SDL_RenderPresent(renderer);
    }
}
