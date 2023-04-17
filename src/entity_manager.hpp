#ifndef __ENTITY_MANAGER_HPP__
#define __ENTITY_MANAGER_HPP__

#include <cstddef>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <utility>
#include <random>

#include "entity.hpp"
#include "grid.hpp"

namespace snake_game {
class EntityManager {
 public:
  using EntityMap = std::unordered_map<size_t, std::unique_ptr<Entity>>;
  enum EntityType { SNAKE, APPLE };
  class EntityManagerIterator {
   public:
    using value_type = Entity;
    using reference = value_type&;
    using pointer = value_type*;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;

    EntityManagerIterator(EntityManager::EntityMap::iterator it) : it_{it} {}

    reference operator*() const { return *(it_->second); }

    pointer operator->() const { return it_->second.get(); }

    EntityManagerIterator& operator++() {
      ++it_;
      return *this;
    }

    EntityManagerIterator operator++(int) {
      EntityManagerIterator temp{*this};
      ++it_;
      return temp;
    }

    bool operator==(const EntityManagerIterator& other) const {
      return it_ == other.it_;
    }

    bool operator!=(const EntityManagerIterator& other) const {
      return !(*this == other);
    }

   private:
    EntityManager::EntityMap::iterator it_;
  };
  EntityManager(std::shared_ptr<Grid> grid) : grid_{grid} {}
  Entity& create_snake(int16_t x, int16_t y);
  Entity& create_apple();

  void remove_entity(size_t enity_id) {
    auto iter = entities_.find(enity_id);
    if (iter != entities_.end()) {
      entities_.erase(iter);
    }
  }

  EntityManagerIterator begin() {
    return EntityManagerIterator(entities_.begin());
  }

  EntityManagerIterator end() { return EntityManagerIterator(entities_.end()); }

 private:
  std::pair<int32_t, int32_t> _get_random_empty_position();
  std::shared_ptr<Grid> grid_;
  std::mt19937 random_number_generator_{std::random_device{}()};
  EntityMap entities_;
  size_t next_id_ = 0;
};
}  // namespace snake_game

#endif
