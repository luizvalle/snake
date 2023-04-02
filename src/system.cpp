#include <stdexcept>
#include <SDL2/SDL.h>
#include "system.hpp"
#include "renderer.hpp"

namespace snake_game {
    void RenderSystem::update(std::vector<Entity>& entities) {
        SDL_Renderer *renderer = Renderer::get_instance().get();
        SDL_RenderClear(renderer);
        for (auto& entity : entities) {
            if (entity.has_component<PositionComponent>()
                && entity.has_component<RectangleRenderComponent>()) {
                _render_normal(entity, renderer);
            } else if (entity.has_component<SnakeComponent>()) {
                _render_snake(entity, renderer);
            }
        }
        SDL_RenderPresent(renderer);
    }

    void RenderSystem::_render_normal(Entity& entity, SDL_Renderer *renderer) {
        const auto& position = entity.get_component<PositionComponent>();
        const auto& render = entity.get_component<RectangleRenderComponent>();
        SDL_Rect rect {position.x, position.y, render.w, render.h};
        SDL_SetRenderDrawColor(renderer,
                render.color.r,
                render.color.g,
                render.color.b,
                render.color.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    void RenderSystem::_render_snake(Entity& entity, SDL_Renderer *renderer) {
        const auto& snake_component = entity.get_component<SnakeComponent>();
        for (const auto& segment : snake_component.segments) {
            const auto& position = segment.position_component;
            const auto& render = segment.render_component;
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
}
