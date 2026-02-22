#include "Systems/AnimationTimeSystem.hpp"


void AnimationTimeSystem(entt::registry& registry, const float dt) 
{
    using namespace Components;

    auto view = registry.view<AnimatedTexture, AnimationClipReference>();

    for (auto [entity, texture, clip]: view.each())
    {
        // Update time_passed (should use a timestamp instead?)
        texture.time_passed += dt;
        // Get frame
        const auto& frame = clip.ref->frames.at(texture.current_frame_index);
        // If frame has appeared for long enough, update frame_index and reset time_passed
        if (texture.time_passed >= frame.duration / 1000.f) 
        {
            // Reset frame_time
            texture.time_passed = 0.0f;
            // Reset frame_index to 0 if total_frames was reached...
            if (1 + texture.current_frame_index >= clip.ref->frames.size())
                texture.current_frame_index = 0;
            // ...otherwise simply increment by 1
            else
                texture.current_frame_index++;
        }
    }
};