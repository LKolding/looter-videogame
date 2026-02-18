#pragma once

#include <glm/glm.hpp>

struct InputState 
{
	// movement
	glm::vec2 move_intent;
	bool is_sprinting;

	// view direction/aim
	float mouseX;
	float mouseY;

	// shoot
	bool player_did_shoot;

};