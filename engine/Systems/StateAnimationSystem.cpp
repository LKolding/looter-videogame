#include "StateAnimationSystem.hpp"


void StateAnimationSystem(entt::registry& registry, const float dt)
{
    using namespace Components;
    
    auto view = registry.view<AnimatedTexture, AnimationClipReference, AnimationSetsReference, StateComponent, Facing>();

    for(auto [entity, texture, clip, sets, state, facing]: view.each()) 
    {
        // animation clip
        if (clip.ref != &sets.ref.at(texture.id)._animations.at(facing.value))
        {
            clip.ref = &sets.ref.at(texture.id)._animations.at(facing.value);
            texture.current_frame_index = 0; // reset (safety)
        }

        // update src_rect
        const auto& current_frame = clip.ref->frames.at(texture.current_frame_index);
        texture.src_rect = {
            .x = static_cast<float>(current_frame.x),
            .y = static_cast<float>(current_frame.y),
            .w = static_cast<float>(current_frame.w),
            .h = static_cast<float>(current_frame.h),
        };
    }
}
