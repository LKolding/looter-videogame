#pragma once

#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <string>

#include "../common/types.hpp"
#include "../common/TextureID.hpp"
#include "../common/Animation.hpp"


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
		Direction value = Direction::South;

		inline std::string to_string(void)
		{
			switch(this->value)
			{
				case Direction::South:
					return {"south"};
					break;

				case Direction::East:
					return {"east"};
					break;

				case Direction::West:
					return {"west"};
					break;

				case Direction::North:
					return {"north"};
					break;
			}
		}
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

	struct StateComponent
	{
        State current = State::Idle;
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
		AnimationClip* ref = nullptr;
	};

	struct AnimationSetsReference
	{
		std::unordered_map<TextureID, AnimationSet>& ref; 
	};

}