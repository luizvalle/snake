#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <list>
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
            void _handle_collisions();
            Window m_window;
            Snake m_snake;
            std::list<Apple> m_apples;
            bool m_game_over = false;
    };
}

#endif
