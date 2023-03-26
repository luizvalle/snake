#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <forward_list>
#include "window.hpp"
#include "snake.hpp"
#include "apple.hpp"

namespace snake_game {
    class Game final {
        public:
            Game();
            Game(const Game&) = delete;
            Game& operator=(Game) = delete;
            Game(const Game&&) = delete;
            Game& operator=(Game&&) = delete;
            void run();
        private:
            void _handle_input();
            void _render();
            bool _is_out_of_bounds(const Sprite& sprite) const {
                return sprite.is_out_of_bounds(window.get_width(),
                                               window.get_height());
            }
            Window window;
            Snake snake;
            std::forward_list<Apple> apples;
            bool game_over = false;
    };
}

#endif
