#include "entity.hpp"
#include "component.hpp"
#include "system.hpp"
#include "renderer.hpp"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

using namespace snake_game;

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Luiz Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          400, 400, 0);

    if (!window) {
        SDL_Quit();
        return 1;
    }

    Renderer& renderer = Renderer::get_instance();
    renderer.init(window);

    std::vector<Entity> entities;
    entities.emplace_back();
    RectangleRenderComponent::Color color {255, 0, 0, 255};
    entities.back().add_component<PositionComponent>(200, 200);
    entities.back().add_component<RectangleRenderComponent>(20, 20, color);

    RenderSystem render_system;

    render_system.update(entities);

    SDL_PumpEvents();

    SDL_Delay(5000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
