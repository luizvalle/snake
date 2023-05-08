#ifndef __ENTITY_MANAGER_HPP__
#define __ENTITY_MANAGER_HPP__

#include <cstddef>
#include <cstdint>
#include <memory>
#include <random>
#include <stdexcept>
#include <list>
#include <utility>

#include "entity.hpp"
#include "grid.hpp"

namespace snake_game {
    class EntityManager {
    public:
        using EntityList = std::list<std::shared_ptr<Entity>>;
        class EntityManagerIterator {
            friend class EntityManager;
        public:
            using value_type = Entity;
            using reference = value_type &;
            using pointer = value_type *;
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;

            EntityManagerIterator(EntityManager::EntityList::iterator it) : it_{it} {}

            reference operator*() const { return **it_; }

            pointer operator->() const { return it_->get(); }

            std::shared_ptr<Entity> operator&() const {
                return *it_;
            }

            EntityManagerIterator &operator++() {
                ++it_;
                return *this;
            }

            EntityManagerIterator operator++(int) {
                EntityManagerIterator temp{*this};
                ++it_;
                return temp;
            }

            bool operator==(const EntityManagerIterator &other) const {
                return it_ == other.it_;
            }

            bool operator!=(const EntityManagerIterator &other) const {
                return !(*this == other);
            }

        private:
            EntityManager::EntityList::iterator it_;
        };
        EntityManager(std::shared_ptr<Grid> grid) : grid_{grid} {}

        std::shared_ptr<Entity> create_snake(int32_t x, int32_t y);

        std::shared_ptr<Entity> create_apple();

        std::shared_ptr<Entity> create_collision(std::weak_ptr<Entity> entity1,
                                                 std::weak_ptr<Entity> entity2);

        void add_segment_to_snake(Entity &entity);

        EntityManagerIterator begin() {
            return EntityManagerIterator(entities_.begin());
        }

        EntityManagerIterator end() {
            return EntityManagerIterator(entities_.end());
        }

        EntityManagerIterator erase(EntityManagerIterator& it) {
            return EntityManagerIterator(entities_.erase(it.it_));
        }

    private:
        std::pair<int32_t, int32_t> _get_random_empty_position();
        std::shared_ptr<Entity> _create_entity() {
            size_t id = next_id_++;
            auto entity_ptr = std::make_shared<Entity>(id);
            return entities_.emplace_back(entity_ptr);
        }
        std::shared_ptr<Entity> _create_snake_segment(int32_t x, int32_t y);
        std::shared_ptr<Grid> grid_;
        std::mt19937 random_number_generator_{std::random_device{}()};
        EntityList entities_;
        size_t next_id_ = 0;
    };
} // namespace snake_game

#endif
