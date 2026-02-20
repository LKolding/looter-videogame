#include "StateSystem.hpp"


void StateSystem(entt::registry& registry, const float dt)
{
    using namespace Components;

    auto view = registry.view<StateComponent, Velocity>();

    for(auto [entity, state, vel]: view.each()) 
    {
        // Update state based on velocity
        if (glm::length(vel.value) > 0.f)
            state.current = State::Moving;
        else
            state.current = State::Idle;
    }
}