#include "StateSystem.hpp"

// Updates State based on Velocity

void StateSystem(entt::registry& registry, const float dt)
{
    using namespace Components;

    auto view = registry.view<State, Velocity>();

    

    for(auto [entity, state, vel]: view.each()) 
    {
        std::string text = glm::length(vel.value) > 0.1 ? "Moving\n" : "Standstill\n";
        std::cout << text;

        // Update state based on velocity
        if (glm::length(vel.value) > 0.f)
            state.current = State::Type::Moving;
        else
            state.current = State::Type::Idle;
    }
}