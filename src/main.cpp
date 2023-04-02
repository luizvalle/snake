#include "entity.hpp"
#include "component.hpp"
#include "system.hpp"
#include "renderer.hpp"
#include "command.hpp"
#include "input_handler.hpp"
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
    entities.back().add_component<SnakeComponent>();
    PositionComponent position {100, 100};
    ColorComponent fill_color {0, 71, 100, 255};
    ColorComponent border_color {0, 0, 0, 255};
    RectangleShapeComponent rect {20, 20};
    RectangleRenderComponent rect_render {rect, fill_color, border_color};
    entities.back().get_component<SnakeComponent>().segments.emplace_back(position,
                                                                          rect_render);
    entities.back().add_component<VelocityComponent>(20, VelocityComponent::Direction::RIGHT);

    RenderSystem render_system;
    MovementSystem movement_system;

    bool game_over = false;

    InputHandler input_handler;
    input_handler.set_quit_command(std::make_unique<QuitCommand>(game_over));
    input_handler.bind_command(SDL_Scancode::SDL_SCANCODE_UP,
                               std::make_unique<ChangeDirectionCommand>(entities.back(), 
                                   VelocityComponent::Direction::UP));
    input_handler.bind_command(SDL_Scancode::SDL_SCANCODE_DOWN,
                               std::make_unique<ChangeDirectionCommand>(entities.back(), 
                                   VelocityComponent::Direction::DOWN));
    input_handler.bind_command(SDL_Scancode::SDL_SCANCODE_LEFT,
                               std::make_unique<ChangeDirectionCommand>(entities.back(), 
                                   VelocityComponent::Direction::LEFT));
    input_handler.bind_command(SDL_Scancode::SDL_SCANCODE_RIGHT,
                               std::make_unique<ChangeDirectionCommand>(entities.back(), 
                                   VelocityComponent::Direction::RIGHT));

    while (!game_over) {
        input_handler.handle_input();
        movement_system.update(entities);
        render_system.update(entities);
        SDL_Delay(10000/60);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
