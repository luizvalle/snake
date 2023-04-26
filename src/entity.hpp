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
            T *component = _get_component<T>();
            return component != nullptr;
        }

        template <typename T>
        T &get_component() {
            T *component = _get_component<T>();
            if (!component) {
                throw std::runtime_error("Could not find component.");
            }
            return *component;
        }

        template <typename T, typename... TArgs>
        T &add_component(TArgs &&...args) {
            T *component = new T(std::forward<TArgs>(args)...);
            components_.emplace_back(component);
            return *component;
        }

        size_t id() const { return id_; }

    private:
        template <typename T>
        T *_get_component() const {
            for (auto &component : components_) {
                T *component_ptr = dynamic_cast<T *>(component.get());
                if (component_ptr) {
                    return component_ptr;
                }
            }
            return nullptr;
        }
        std::vector<std::unique_ptr<Component>> components_;
        size_t id_;
    };
} // namespace snake_game

#endif
