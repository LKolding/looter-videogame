#include "StateAnimationSystem.hpp"

/*
Updates both AnimatedTexture based on State and Facing,
and AnimationClipReference based on AnimatedTexture.texture_id
*/

void StateAnimationSystem(entt::registry& registry, const float dt)
{
    using namespace Components;
    
    auto view = registry.view<AnimatedTexture, AnimationClipReference, AnimationSetsReference, State, Facing>();

    for(auto [entity, texture, clip, sets, state, facing]: view.each()) 
    {
        const auto stateIndex  = static_cast<uint8_t>(state.current);
        const auto facingIndex = static_cast<uint8_t>(facing.value);

        // temp
        // reset to ensure a _frame_ of the sprite is shown and not just blank space
        texture.src_rect.x = 0; // (doesn't fix the problem currently)

        // texture id
        texture.id = 1 + stateIndex;

        // animation clip
        clip.ref = sets.ref.at(texture.id).animations.at(facingIndex);

        // sprite row
        texture.src_rect.y = facingIndex * texture.src_rect.h;

        // sprite column
        texture.src_rect.x = texture.src_rect.w * texture.current_frame_index;
    }
}
