#include "VelocitySystem.hpp"


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
    
    auto view = registry.view<Velocity, MovementIntent, MovementStats, Facing>();

    for (auto entity : view)
    {
        auto& vel = view.get<Velocity>(entity);
        auto& mov = view.get<MovementIntent>(entity);
        auto& stats=view.get<MovementStats>(entity);
        auto& facing=view.get<Facing>(entity);

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

        // Facing
        if (vel.value.length() > 0.0f) {
            if (std::abs(vel.value.x) > std::abs(vel.value.y))
                facing.value = vel.value.x > 0 ? Facing::Direction::East : Facing::Direction::West;
            else
                facing.value = vel.value.y > 0 ? Facing::Direction::South : Facing::Direction::North;
        }
    }
}
