#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

#include "component.hpp"

namespace snake_game {
class Entity {
 public:
  Entity(size_t id) : m_id{id} {}
  template <typename T>
  bool has_component() const {
    T* component = _get_component<T>();
    return component != nullptr;
  }

  template <typename T>
  T& get_component() {
    T* component = _get_component<T>();
    if (!component) {
      throw std::runtime_error("Could not find component.");
    }
    return *component;
  }

  template <typename T, typename... TArgs>
  T& add_component(TArgs&&... args) {
    T* component = new T(std::forward<TArgs>(args)...);
    m_components.emplace_back(component);
    return *component;
  }

 private:
  template <typename T>
  T* _get_component() const {
    for (auto& component : m_components) {
      T* component_ptr = dynamic_cast<T*>(component.get());
      if (component_ptr) {
        return component_ptr;
      }
    }
    return nullptr;
  }
  std::vector<std::unique_ptr<Component>> m_components;
  size_t m_id;
};
}  // namespace snake_game

#endif
