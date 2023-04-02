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
                const auto& position = entity.get_component<PositionComponent>();
                const auto& render = entity.get_component<RectangleRenderComponent>();
                _render_normal(position, render);
            } else if (entity.has_component<SnakeComponent>()) {
                _render_snake(entity);
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
    }

    void RenderSystem::_render_normal(const PositionComponent& position,
                                      const RectangleRenderComponent& render) {
        SDL_Renderer *renderer = Renderer::get_instance().get();
        SDL_Rect rect {position.x, position.y, render.rect.w, render.rect.h};
        SDL_SetRenderDrawColor(renderer,
                render.fill_color.r,
                render.fill_color.g,
                render.fill_color.b,
                render.fill_color.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer,
                render.border_color.r,
                render.border_color.g,
                render.border_color.b,
                render.border_color.a);
        SDL_RenderDrawRect(renderer, &rect);
    }

    void RenderSystem::_render_snake(Entity& entity) {
        const auto& snake_component = entity.get_component<SnakeComponent>();
        for (const auto& segment : snake_component.segments) {
            const auto& position = segment.position_component;
            const auto& render = segment.rectangle_render_component;
            _render_normal(position, render);
        }
    }

    void MovementSystem::update(std::vector<Entity>& entities) {
        for (auto& entity : entities) {
            if (entity.has_component<SnakeComponent>()
                && entity.has_component<VelocityComponent>()) {
                _move_snake(entity);
            }
        }
    }

    void MovementSystem::_move_snake(Entity& entity) {
        auto& segments = entity.get_component<SnakeComponent>().segments;
        const auto& velocity_component = entity.get_component<VelocityComponent>();
        const auto& head = segments.front();
        int16_t new_x = head.position_component.x;
        int16_t new_y = head.position_component.y;
        switch (velocity_component.direction) {
            case VelocityComponent::Direction::UP:
                new_y -= velocity_component.speed;
                break;
            case VelocityComponent::Direction::DOWN:
                new_y += velocity_component.speed;
                break;
            case VelocityComponent::Direction::LEFT:
                new_x -= velocity_component.speed;
                break;
            case VelocityComponent::Direction::RIGHT:
                new_x += velocity_component.speed;
                break;
        }
        auto& tail = segments.back();
        tail.position_component.x = new_x;
        tail.position_component.y = new_y;
        segments.splice(segments.begin(), segments, --segments.end());
    }
}
