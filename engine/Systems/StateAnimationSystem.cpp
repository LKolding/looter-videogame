#include "StateAnimationSystem.hpp"

/*
Updates both AnimatedTexture based on State and Facing,
and AnimationClipReference based on AnimatedTexture.texture_id
*/

void StateAnimationSystem(entt::registry& registry, const float dt)
{
    using namespace Components;
    
    auto view = registry.view<AnimatedTexture, AnimationClipReference, AnimationSetsReference, State, Facing>();

    for (auto entity : view)
    {
        auto& texture = view.get<AnimatedTexture>(entity);
        auto& clipRef = view.get<AnimationClipReference>(entity);
        
        const auto& setsRef = view.get<AnimationSetsReference>(entity);
        const auto& state = view.get<State>(entity);
        const auto& facing = view.get<Facing>(entity);

        const auto stateIndex = static_cast<uint8_t>(state.current);
        const auto facingIndex = static_cast<uint8_t>(facing.value);

        // texture id
        texture.id = stateIndex + 1;

        // animation clip
        clipRef.ref = setsRef.ref.at(texture.id).animations.at(facingIndex);

        // sprite row
        texture.src_rect.y = facingIndex * texture.src_rect.h;

        // sprite column
        texture.src_rect.x = texture.src_rect.w * texture.current_frame_index;

    }
}
