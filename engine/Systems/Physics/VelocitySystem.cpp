#include "VelocitySystem.hpp"


const float EPSILON = 0.1f; // tweak to taste


glm::vec2 approach(
    const glm::vec2& current,
    const glm::vec2& target,
    const float maxDelta)
{
    glm::vec2 delta = target - current;
    float dist = delta.length();

    if (dist <= maxDelta || dist == 0.0f)
        return target;

    return current + delta / dist * maxDelta;
}


void VelocitySystem(entt::registry& registry, const float dt)
{
    using namespace Components;
    auto view = registry.view<Velocity, MovementIntent, MovementStats, Facing>();

    for (auto [entity, velocity, moveIntent, moveStats, facing]: view.each())
    {
        // Move intent
        glm::vec2 intent = moveIntent.value;
        if (glm::length(intent) > EPSILON)
            intent = glm::normalize(intent);

        // Facing (update based on intent)
        if (glm::length(intent) > 0.f) {
            if (std::abs(intent.x) > std::abs(intent.y))
                facing.value = intent.x > 0 ? Facing::Direction::East : Facing::Direction::West;
            else
                facing.value = intent.y > 0 ? Facing::Direction::South : Facing::Direction::North;
        }

        // Target velocity
        glm::vec2 targetVelocity = 
            intent * moveStats.max_speed;

        // Acceleration
        const float rate = (glm::length(moveIntent.value) > 0.f)
            ? moveStats.acceleration
            : moveStats.deceleration;

        // Approach
        velocity.value = approach(
            velocity.value,
            targetVelocity,
            rate * dt
        );

        // Clamp
        if (glm::length(velocity.value) < EPSILON)
            velocity.value = glm::vec2(0.f);
    }
}
