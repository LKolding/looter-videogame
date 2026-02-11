#pragma once

#include <SDL3/SDL.h>

#include "../common/InputState.hpp"


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

private:
	InputState handle_kbm();
	InputState handle_cntrl();

	InputState current_input_state;
public:
	InputState& get_input_state();

};