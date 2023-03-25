#include <iostream>
#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "window.hpp"
#include "snake.hpp"
#include "apple.hpp"
#include "controller.hpp"

using namespace std;

constexpr size_t WINDOW_WIDTH = 640, WINDOW_HEIGHT = 480;

int main(void) {
    snake_game::Window window {WINDOW_WIDTH, WINDOW_HEIGHT, "Snake"};


    snake_game::Snake snake {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 3, 20};
    snake.change_direction(snake_game::Direction::RIGHT);

    snake_game::Apple apple {WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, 20};

    bool close_window = false;

    int i = 0;
    while (!close_window) {
        switch (snake_game::get_action()) {
            case snake_game::EXIT:
                close_window = true;
                break;
            case snake_game::MOVE_UP:
                snake.change_direction(snake_game::Direction::UP);
                break;
            case snake_game::MOVE_DOWN:
                snake.change_direction(snake_game::Direction::DOWN);
                break;
            case snake_game::MOVE_LEFT:
                snake.change_direction(snake_game::Direction::LEFT);
                break;
            case snake_game::MOVE_RIGHT:
                snake.change_direction(snake_game::Direction::RIGHT);
                break;
            default:
                break;
        }
        snake.move();
        window.clear();
        window.render(snake);
        window.render(apple);
        window.show();
        if (snake.is_out_of_bounds(WINDOW_WIDTH, WINDOW_HEIGHT)
            || snake.self_collided()) {
            close_window = true;
        }
        if (snake.collided_with(apple)) {
            snake.add_segment();
        }
        SDL_Delay(7000 / 60);
    }

    return 0;
}
