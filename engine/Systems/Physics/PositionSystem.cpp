#include "PositionSystem.hpp"

// Updates Position based on Velocity

void PositionSystem(entt::registry& registry, float dt)
{
    using namespace Components;

    auto view = registry.view<Velocity, Position>();

    for (auto entity : view)
    {
        auto& vel = view.get<Velocity>(entity);
        auto& pos = view.get<Position>(entity);
        
        pos.x += vel.value.x * dt;
        pos.y += vel.value.y * dt;

    }
}
