#ifndef __ENTITY_MANAGER_HPP__
#define __ENTITY_MANAGER_HPP__

#include <cstddef>
#include <cstdint>
#include <memory>
#include <random>
#include <stdexcept>
#include <unordered_map>
#include <utility>

#include "entity.hpp"
#include "grid.hpp"

namespace snake_game {
    class EntityManager {
    public:
        using EntityMap = std::unordered_map<size_t, std::unique_ptr<Entity>>;
        class EntityIterator {
        public:
            using value_type = Entity;
            using reference = value_type &;
            using pointer = value_type *;
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;

            EntityIterator(EntityManager::EntityMap::iterator it) : it_{it} {}

            reference operator*() const { return *(it_->second); }

            pointer operator->() const { return it_->second.get(); }

            EntityIterator &operator++() {
                ++it_;
                return *this;
            }

            EntityIterator operator++(int) {
                EntityIterator temp{*this};
                ++it_;
                return temp;
            }

            bool operator==(const EntityIterator &other) const {
                return it_ == other.it_;
            }

            bool operator!=(const EntityIterator &other) const {
                return !(*this == other);
            }

        private:
            EntityManager::EntityMap::iterator it_;
        };
        EntityManager(std::shared_ptr<Grid> grid) : grid_{grid} {}
        Entity &create_snake(int16_t x, int16_t y);
        Entity &create_apple();

        Entity &get_entity(size_t entity_id) {
            auto iter = entities_.find(entity_id);
            if (iter != entities_.end()) {
                return *(iter->second);
            }
            throw std::runtime_error("An entity with the given id does not exist.");
        }

        void remove_entity(size_t entity_id) {
            auto iter = entities_.find(entity_id);
            if (iter != entities_.end()) {
                entities_.erase(iter);
            }
        }

        void add_segment_to_snake(size_t entity_id);

        EntityIterator begin() {
            return EntityIterator(entities_.begin());
        }

        EntityIterator end() { return EntityIterator(entities_.end()); }

    private:
        std::pair<int32_t, int32_t> _get_random_empty_position();
        std::shared_ptr<Grid> grid_;
        std::mt19937 random_number_generator_{std::random_device{}()};
        EntityMap entities_;
        size_t next_id_ = 0;
    };
} // namespace snake_game

#endif
