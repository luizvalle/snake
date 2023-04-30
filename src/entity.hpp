#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <typeinfo>
#include <vector>

#include "component.hpp"

namespace snake_game {
    class Entity {
    public:
        Entity(size_t id) : id_{id} {}
        template <typename T>
        bool has_component() const {
            auto component_ptr = _get_component<T>();
            return component_ptr != nullptr;
        }

        template <typename T>
        std::shared_ptr<T> get_component() {
            auto component_ptr = _get_component<T>();
            if (!component_ptr) {
                throw std::runtime_error("Could not find component.");
            }
            return std::static_pointer_cast<T>(component_ptr);
        }

        template <typename T, typename... TArgs>
        std::shared_ptr<T> add_component(TArgs &&...args) {
            T *component = new T(std::forward<TArgs>(args)...);
            auto component_ptr = components_.emplace_back(component);
            return std::static_pointer_cast<T>(component_ptr);
        }

        size_t id() const { return id_; }

        bool operator==(const Entity& other) const {
            return id() == other.id();
        }

    private:
        template <typename T>
        std::shared_ptr<T> _get_component() const {
            for (auto &component_ptr : components_) {
                auto ptr = std::dynamic_pointer_cast<T>(component_ptr);
                if (ptr) {
                    return ptr;
                }
            }
            return nullptr;
        }
        std::vector<std::shared_ptr<Component>> components_;
        size_t id_;
    };
} // namespace snake_game

#endif
