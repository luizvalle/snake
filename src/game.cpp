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
        : m_window{WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME},
        m_snake{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, SNAKE_INIT_LENGTH,
                SNAKE_WIDTH}
    {}

    void Game::run() {
        while (!m_game_over) {
            uint64_t start = SDL_GetPerformanceCounter();
            _handle_input();
            m_snake.move();
            _render();
            _handle_collisions();
            uint64_t end = SDL_GetPerformanceCounter();
            float elapsed_ms = (end - start) / static_cast<float>(
                    SDL_GetPerformanceFrequency()) * 1000.0f;
            SDL_Delay(static_cast<uint32_t>(
                        MILLISECOND_DELAY_BETWEEN_FRAMES - elapsed_ms));
        }
    }

    void Game::_handle_input() {
        Action a = get_action();
        if (a == EXIT) {
            m_game_over = true;
            return;
        }
        Action last_action = a;
        for (; a != NO_OP; last_action = a, a = get_action()) {}
        switch (last_action) {
            case MOVE_UP:
                m_snake.set_direction(Direction::UP);
                break;
            case MOVE_DOWN:
                m_snake.set_direction(Direction::DOWN);
                break;
            case MOVE_LEFT:
                m_snake.set_direction(Direction::LEFT);
                break;
            case MOVE_RIGHT:
                m_snake.set_direction(Direction::RIGHT);
                break;
            default:
                break;
        }
    }

    void Game::_render() {
        using namespace std::placeholders;
        m_window.clear();
        m_window.render(m_snake);
        std::for_each(m_apples.begin(),
                      m_apples.end(),
                      std::bind(&Window::render, &m_window, _1));
        m_window.show();
    }

    void Game::_handle_collisions() {
        size_t window_width = m_window.get_width();
        size_t window_height = m_window.get_height();
        if (m_snake.self_collided()
            || m_snake.is_out_of_bounds(window_width, window_height)) {
            m_game_over = true;
            return;
        }
    }
}
