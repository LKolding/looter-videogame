#pragma once

#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <string>

#include "../common/types.hpp"
#include "../common/TextureID.hpp"
#include "../common/AnimationClip.hpp"


namespace Components
{
	struct Position 
	{
		float x = 0.0f;
		float y = 0.0f;
	};
	
	struct Velocity
	{
		glm::vec2 value{0.0f, 0.0f};
		float max = 300.0f;
	};

	struct Facing
	{
		// Matches sprite sheet row order (crucial for animation)
		// 0 = South, 1 = West, 2 = East, 3 = North
		enum class Direction : uint8_t
		{
			South = 0,
			West  = 1,
			East  = 2,
			North = 3
		};
		Direction value = Direction::South;
	};

	struct MovementIntent
	{
		glm::vec2 value{0.0f, 0.0f};
	};
	
	struct MovementStats
	{
		float acceleration  = 1200.0f;
		float deceleration = 1200.0f;
		float max_speed = 250.0f;
	};

	struct State
	{
        enum class Type : uint8_t { Moving=0, Idle=1, Attacking=2 };
        Type current = Type::Idle;
    };

	struct Texture
	{
		TextureID id = 0;
		SDL_FRect src_rect = { 0,0,0,0 };
	};

	struct AnimatedTexture
	{
		TextureID id = 0;
		SDL_FRect src_rect = { 0,0,0,0 }; // I should remove SDL from engine

		uint16_t current_frame_index = 0;
		float time_passed = 0.0f;
	};

	struct AnimationClipReference
	{
		AnimationClip& ref;
	};

	struct AnimationSetsReference
	{
		const std::unordered_map<TextureID, AnimationSet>& ref; 
	};

}