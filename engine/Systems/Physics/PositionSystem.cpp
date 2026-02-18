#include "PositionSystem.hpp"

// Updates Position based on Velocity

void PositionSystem(entt::registry& registry, float dt)
{
    using namespace Components;

    auto view = registry.view<Velocity, Position>();

    for (auto [entity, velocity, position]: view.each())
    {
        position.x += velocity.value.x * dt;
        position.y += velocity.value.y * dt;
    }
}
