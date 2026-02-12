#include "VelocitySystem.hpp"

/*
This system is calculating acceleration based on Movement and MovementStats.
Then, it calculates Velocity based on acceleration.
*/


Vec2 approach(const Vec2& current,
              const Vec2& target,
              float maxDelta)
{
    Vec2 delta = target - current;
    float dist = delta.length();

    if (dist <= maxDelta || dist == 0.0f)
        return target;

    return current + delta / dist * maxDelta;
}


void VelocitySystem(entt::registry& registry, const float dt)
{
    using namespace Components;
    
    auto view = registry.view<Velocity, Movement, MovementStats>();

    for (auto entity : view)
    {
        auto& vel = view.get<Velocity>(entity);
        auto& mov = view.get<Movement>(entity);
        auto& stats=view.get<MovementStats>(entity);

        // Movement intent
        if (mov.value.length() > 1.0f)
        {
            mov.value = mov.value.normalized();
        }

        // Acceleration
        float accelerationX = mov.value.x * stats.acceleration;
        float accelerationY = mov.value.y * stats.acceleration;

        // Velocity
        vel.value.x += accelerationX * dt;
        vel.value.y += accelerationY * dt;

        Vec2 targetVelocity {mov.value.x * stats.max_speed, mov.value.y * stats.max_speed};

        vel.value = approach(
            vel.value,
            targetVelocity,
            stats.acceleration * dt
        );
    }
}
