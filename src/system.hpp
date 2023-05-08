#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#include <memory>
#include <vector>

#include "entity.hpp"
#include "entity_manager.hpp"
#include "graphics.hpp"
#include "grid.hpp"

namespace snake_game {
    struct System {
        virtual ~System() {}
        virtual void update(EntityManager &entity_manager) = 0;
    };

    class RenderSystem final : public System {
    public:
        RenderSystem(std::shared_ptr<Graphics> graphics,
                     std::shared_ptr<Grid> grid)
            : graphics_{graphics}, grid_{grid} {}
        virtual void update(EntityManager &entity_manager) override;

    private:
        std::shared_ptr<Graphics> graphics_;
        std::shared_ptr<Grid> grid_;
    };

    class MovementSystem : public System {
    public:
        MovementSystem(std::shared_ptr<Grid> grid) : grid_{grid} {}
        virtual void update(EntityManager &entity_manager) override;

    private:
        void _move_snake(Entity &entity);
        std::shared_ptr<Grid> grid_;
    };

    class CollisionDetectionSystem : public System {
    public:
        virtual void update(EntityManager &entity_manager) override;
    };

    class CollisionHandlerSystem : public System {
    public:
        virtual void update(EntityManager &entity_manager) override;
    private:
        void _delete_snake(Entity &snake_head) const;
    };

    class GarbageCollectorSystem : public System {
    public:
        virtual void update(EntityManager &entity_manager) override;
    };
} // namespace snake_game

#endif
