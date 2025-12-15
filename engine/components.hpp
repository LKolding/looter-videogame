#pragma once

#include "Managers/TextureManager.hpp"


struct Position {
	float x = 0.0f;
	float y = 0.0f;
};

struct Velocity {
	float speed = 1.0f;
	float dx = 0.0f;
	float dy = 0.0f;
};

struct Hitbox {
	float radius = 0.0f;
};

struct Texture {
	TextureID id = 0;
	SDL_FRect src_rect = { 0,0,0,0 };
};

struct TextureAnimation {
	uint16_t total_frames = 0;
	float frame_time = 1.0f;

	uint16_t current_frame_index = 0;
	float time_passed = 0.0f;
};
