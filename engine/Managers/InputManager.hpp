#pragma once

#include <SDL3/SDL.h>


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


enum INPUT_TYPE {
	CNTRL, // controller/gamepad
	KBM	   // keyboard & mouse
};


class InputManager {
private:
	INPUT_TYPE selected_input = KBM;

public:
	//bool change_input_type(INPUT_TYPE new_input_type);

	void update();
	InputState& get_input_state();

private:
	InputState handle_kbm();
	InputState handle_cntrl();

	InputState current_input_state;

};