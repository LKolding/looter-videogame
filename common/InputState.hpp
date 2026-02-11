#pragma once

struct InputState {
	// movement
	float moveX = 0;
	float moveY = 0;
	bool is_sprinting = false;
	// view direction/aim
	float lookX = 0;
	float lookY = 0;
	// shoot
	bool player_did_shoot = false;

};