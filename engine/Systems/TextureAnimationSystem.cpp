#include "Systems/TextureAnimationSystem.hpp"
#include "components.hpp"


void TextureAnimationSystem(entt::registry& registry, const float dt) 
{
    auto view = registry.view<Texture, TextureAnimation>();

    for (auto entity : view)
    {
        auto& texture_component = view.get<Texture>(entity);
        auto& animation_component = view.get<TextureAnimation>(entity);

        // Update time_passed (should use a timestamp instead)
        animation_component.time_passed += dt;

        /// Ensure current_animation matches with the src_rect.y coordinate
        auto tex_height = texture_component.src_rect.h;
        auto cur_animat = animation_component.current_animation;
        texture_component.src_rect.y = cur_animat * tex_height;

        // Early exit if frame is still supposed to appear
        if (animation_component.time_passed < animation_component.frame_time)
            continue;

        // If frame has appeared for long enough, update frame_index and reset time_passed
        else if (animation_component.time_passed >= animation_component.frame_time) 
        {
            // Reset frame_time
            animation_component.time_passed = 0.0f;

            // Reset frame_index to 0 if total_frames was reached...
            if (1 + animation_component.current_frame_index >= animation_component.total_frames)
                animation_component.current_frame_index = 0;

            // ...otherwise simply increment by 1
            else
                animation_component.current_frame_index++;

            // Lastly, update the src_rect to apply new frame of spritesheet/texturesheet
            auto& texture_component = registry.get<Texture>(entity);
            texture_component.src_rect.x = texture_component.src_rect.w * animation_component.current_frame_index;
        }
        
    }
};