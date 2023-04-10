#ifndef __ENTITY_MANAGER_HPP__
#define __ENTITY_MANAGER_HPP__

#include <cstddef>
#include <cstdint>
#include <memory>
#include <unordered_map>

#include "entity.hpp"

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

    EntityManagerIterator(EntityManager::EntityMap::iterator it) : m_it{it} {}

    reference operator*() const { return *(m_it->second); }

    pointer operator->() const { return m_it->second.get(); }

    EntityManagerIterator& operator++() {
      ++m_it;
      return *this;
    }

    EntityManagerIterator operator++(int) {
      EntityManagerIterator temp{*this};
      ++m_it;
      return temp;
    }

    bool operator==(const EntityManagerIterator& other) const {
      return m_it == other.m_it;
    }

    bool operator!=(const EntityManagerIterator& other) const {
      return !(*this == other);
    }

   private:
    EntityManager::EntityMap::iterator m_it;
  };

  Entity& create_entity(EntityType type, int16_t x, int16_t y, uint16_t size);

  void remove_entity(size_t enity_id) {
    auto iter = m_entities.find(enity_id);
    if (iter != m_entities.end()) {
      m_entities.erase(iter);
    }
  }

  EntityManagerIterator begin() {
    return EntityManagerIterator(m_entities.begin());
  }

  EntityManagerIterator end() {
    return EntityManagerIterator(m_entities.end());
  }

 private:
  Entity* _create_snake(size_t id, int16_t x, int16_t y, uint16_t size);
  Entity* _create_apple(size_t id, int16_t x, int16_t y, uint16_t size);
  EntityMap m_entities;
  size_t m_next_id = 0;
};
}  // namespace snake_game

#endif
