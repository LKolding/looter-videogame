#include "MovementSystem.hpp"

void MovementSystem(entt::registry& registry) 
{
    auto view = registry.view<Position, Velocity>();

    for (auto entity : view) {
        auto& pos = view.get<Position>(entity);
        auto& vel = view.get<Velocity>(entity);
        pos.x += vel.dx;
        pos.y += vel.dy;
    }
}
