#include "Systems/TextureAnimationSystem.hpp"


void TextureAnimationSystem(entt::registry& registry, const float dt) 
{
    using namespace Components;

    auto view = registry.view<AnimatedTexture, AnimationClipReference>();

    for (auto entity : view)
    {
        auto& texture = view.get<AnimatedTexture>(entity);
        const auto& animation_clip = view.get<AnimationClipReference>(entity);

        // Update time_passed (should use a timestamp instead)
        texture.time_passed += dt;

        // If frame has appeared for long enough, update frame_index and reset time_passed
        if (texture.time_passed >= animation_clip.ref.frame_time) 
        {
            // Reset frame_time
            texture.time_passed = 0.0f;

            // Reset frame_index to 0 if total_frames was reached...
            if (1 + texture.current_frame_index >= animation_clip.ref.frame_count)
                texture.current_frame_index = 0;

            // ...otherwise simply increment by 1
            else
                texture.current_frame_index++;
        }
    }
};