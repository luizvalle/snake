#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <functional>
#include <SDL2/SDL_timer.h>
#include "game.hpp"
#include "controller.hpp"

static constexpr size_t GRID_SIZE = 20;
static constexpr size_t WINDOW_SIZE_MULTIPLIER = 30;
static constexpr size_t WINDOW_WIDTH = GRID_SIZE * WINDOW_SIZE_MULTIPLIER;
static constexpr size_t WINDOW_HEIGHT = WINDOW_WIDTH;
static const char *GAME_NAME = "Snake";
static constexpr size_t SNAKE_INIT_LENGTH = 3;
static constexpr size_t SNAKE_WIDTH = GRID_SIZE;
static constexpr size_t FPS = 10;
static constexpr float MILLISECOND_DELAY_BETWEEN_FRAMES = 1000 / FPS;

namespace snake_game {
    Game::Game() 
        : window{WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME},
        snake{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, SNAKE_INIT_LENGTH, SNAKE_WIDTH}
    {}

    void Game::run() {
        while (!game_over) {
            uint64_t start = SDL_GetPerformanceCounter();
            _handle_input();
            snake.move();
            _render();
            if (snake.self_collided() ||
                _is_out_of_bounds(snake)) {
                game_over = true;
            }
            uint64_t end = SDL_GetPerformanceCounter();
            float elapsed_ms = (end - start) / static_cast<float>(
                    SDL_GetPerformanceFrequency()) * 1000.0f;
            SDL_Delay(static_cast<uint32_t>(
                        MILLISECOND_DELAY_BETWEEN_FRAMES - elapsed_ms));
        }
    }

    void Game::_handle_input() {
        switch (get_action()) {
            case EXIT:
                game_over = true;
                break;
            case MOVE_UP:
                snake.change_direction(Direction::UP);
                break;
            case MOVE_DOWN:
                snake.change_direction(Direction::DOWN);
                break;
            case MOVE_LEFT:
                snake.change_direction(Direction::LEFT);
                break;
            case MOVE_RIGHT:
                snake.change_direction(Direction::RIGHT);
                break;
            default:
                break;
        }
    }

    void Game::_render() {
        using namespace std::placeholders;
        window.clear();
        window.render(snake);
        std::for_each(apples.begin(),
                      apples.end(),
                      std::bind(&Window::render, &window, _1));
        window.show();
    }
}

