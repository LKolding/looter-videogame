#include "VelocitySystem.hpp"

void VelocitySystem(entt::registry& registry, const float dt)
{
    using namespace Components;
    
    auto view = registry.view<Position, Velocity>();

    for (auto entity : view) 
    {
        auto& vel = view.get<Velocity>(entity);

        // early exit if no velocity
        if (vel.dx == 0.0f && vel.dy == 0.0f)
            continue;  

        auto& pos = view.get<Position>(entity);

        pos.x += vel.dx * vel.speed * dt;
        pos.y += vel.dy * vel.speed * dt;

    }
}
