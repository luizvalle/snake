#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <vector>
#include <memory>
#include <stdexcept>
#include "component.hpp"

namespace snake_game {
    class Entity {
        public:
            template<typename T>
            T& get_component() {
                for (auto& component : components) {
                    T *component_ptr = dynamic_cast<T*>(component.get());
                    if (component_ptr) {
                        return *component_ptr;
                    }
                }
                throw new std::runtime_error("Component not found.");
            }

            template<typename T, typename... TArgs>
            T& add_component(TArgs&&... args) {
                T *component = new T(std::forward<TArgs>(args)...);
                components.emplace_back(component);
                return *component;
            }
        private:
            std::vector<std::unique_ptr<Component>> components;
    };
}

#endif
