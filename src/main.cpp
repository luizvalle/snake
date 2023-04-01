#include "entity.hpp"
#include "component.hpp"
#include <iostream>

using namespace snake_game;

int main(void) {
    Entity e;

    e.add_component<PositionComponent>(1, 2);

    std::cout << e.get_component<VelocityComponent>().speed << '\n';

    return 0;
}
