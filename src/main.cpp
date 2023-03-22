#include <iostream>
#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "window.hpp"
#include "snake.hpp"
#include "controller.hpp"

using namespace std;

constexpr size_t WINDOW_WIDTH = 640, WINDOW_HEIGHT = 480;

int main(void)
{
    snake::Window window {WINDOW_WIDTH, WINDOW_HEIGHT, "Snake"};


    snake::Snake snake {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 3, 20};
    snake.change_direction(snake::Direction::RIGHT);

    bool close_window = false;

    int i = 0;
    while (!close_window) {
        switch (snake::get_action()) {
            case snake::EXIT:
                close_window = true;
                break;
            case snake::MOVE_UP:
                snake.change_direction(snake::Direction::UP);
                break;
            case snake::MOVE_DOWN:
                snake.change_direction(snake::Direction::DOWN);
                break;
            case snake::MOVE_LEFT:
                snake.change_direction(snake::Direction::LEFT);
                break;
            case snake::MOVE_RIGHT:
                snake.change_direction(snake::Direction::RIGHT);
                break;
            default:
                break;
        }
        snake.move();
        window.clear();
        window.render(snake);
        window.show();
        SDL_Delay(5000 / 60);
    }

    return 0;
}
