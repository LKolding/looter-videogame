#pragma once

struct InputState 
{
	// movement
	float moveX;
	float moveY;
	bool is_sprinting;

	// view direction/aim
	float lookX;
	float lookY;

	// shoot
	bool player_did_shoot;

};