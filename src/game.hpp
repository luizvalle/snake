#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <memory>

#include "entity_manager.hpp"
#include "graphics.hpp"
#include "input_handler.hpp"
#include "system.hpp"

namespace snake_game {
    class Game {
    public:
        Game(std::shared_ptr<Graphics> graphics,
             std::unique_ptr<EntityManager> entity_manager,
             std::unique_ptr<InputHandler> input_handler);
        void add_system(std::unique_ptr<System> system) {
            systems_.emplace_back(std::move(system));
        }
        void start();

    private:
        std::shared_ptr<Graphics> graphics_;
        std::unique_ptr<EntityManager> entity_manager_;
        std::unique_ptr<InputHandler> input_handler_;
        std::vector<std::unique_ptr<System>> systems_;
        bool game_over_ = false;
    };
} // namespace snake_game

#endif