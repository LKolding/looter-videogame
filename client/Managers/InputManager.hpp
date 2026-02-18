#pragma once

#include <SDL3/SDL.h>

#include "../common/InputState.hpp"


enum class InputType 
{
	CNTRL, // controller/gamepad
	KBM	   // keyboard & mouse
};


class InputManager 
{
private:
	InputType selected_input = InputType::KBM;
	InputState current_input_state;

public:
	//bool change_input_type(INPUT_TYPE new_input_type);
	void update();
	const InputState& get_input_state();

private:
	InputState handle_kbm();
	InputState handle_cntrl();

};