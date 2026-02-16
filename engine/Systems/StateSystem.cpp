#include "StateSystem.hpp"

// Updates State based on Velocity

void StateSystem(entt::registry& registry, const float dt)
{
    using namespace Components;

    auto view = registry.view<State, Velocity, MovementIntent>();

    for (auto entity : view)
    {
        auto& state_component = view.get<State>(entity);
        auto& velocity_component = view.get<Velocity>(entity);
        auto& movement_component = view.get<MovementIntent>(entity);

        // Update state based on velocity
        if (velocity_component.value.length() > 0.2f)
            state_component.current = State::Type::Moving;
        else
            state_component.current = State::Type::Idle;

    }
}