#pragma once

#include <SDL3/SDL.h>

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
	std::string filename = "";
	SDL_FRect src_rect = { 0,0,0,0 };
};

struct TextureAnimation {
	uint16_t total_frames = 0;//<- if 0, will skip animation until frame_time has passed
	float frame_time = 1.0f;//<- time in ms(?) per frame

	uint16_t current_frame_index = 0;
	float time_passed = 0.0f;//<- this is fucking awful, let's be honest

	uint8_t current_animation = 0;// Amount of "frames"/sprites per sheet can be calculated from TextureComponent (rect w&h/tex.size)
};
