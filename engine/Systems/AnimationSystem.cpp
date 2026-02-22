#include "AnimationSystem.hpp"


void AnimationSystem(entt::registry& registry, const float dt)
{
    using namespace Components;
    
    auto view = registry.view<AnimatedTexture, AnimationClipReference, AnimationSetsReference, StateComponent, Facing>();

    for(auto [entity, texture, clip, set, state, facing]: view.each()) 
    {
        const auto& _set = set.ref.at(texture.id);
        const auto& _clip = _set.clips.at(facing.value);
        const auto& current_frame = _clip.frames.at(texture.current_frame_index);
        
        const AnimationClip* _clip_ptr = &set.ref.at(texture.id).clips.at(facing.value);

        // animation clip
        if (clip.ref != _clip_ptr)
        {
            clip.ref = &set.ref.at(texture.id).clips.at(facing.value);
            texture.current_frame_index = 0; // reset (safety)
        }
        
        // update src_rect
        texture.src_rect = {
            .x = static_cast<float>(current_frame.x),
            .y = static_cast<float>(current_frame.y),
            .w = static_cast<float>(current_frame.w),
            .h = static_cast<float>(current_frame.h),
        };
    }
}
