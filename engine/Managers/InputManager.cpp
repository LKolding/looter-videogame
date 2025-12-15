#include "InputManager.hpp"


void InputManager::update() {
	switch (this->selected_input) {
	case KBM:
		this->current_input_state = handle_kbm();
		break;

	case CNTRL:
		this->current_input_state = handle_cntrl();
		break;

	default:
		break; // handle error (e.g if no input scheme was selected)
	}
}

InputState& InputManager::get_input_state() {
	return current_input_state;
}

InputState InputManager::handle_kbm() {
	const bool* key_states = SDL_GetKeyboardState(NULL);  //<- (should be caching this I think)

	// Movement
	float moveX = 0.0f;
	float moveY = 0.0f;
	bool is_sprinting = false;

	if (key_states[SDL_SCANCODE_W]) {
		moveY = -1.0f; // up
	}
	if (key_states[SDL_SCANCODE_A]) {
		moveX = -1.0f; // left
	}
	if (key_states[SDL_SCANCODE_S]) {
		moveY = 1.0f;  // down
	}
	if (key_states[SDL_SCANCODE_D]) {
		moveX = 1.0f;  // right
	}
	if (key_states[SDL_SCANCODE_LSHIFT]) {
		is_sprinting = true; // shift (sprint)
	}

	// Shooting
	bool did_shoot = false;

	float mouse_x, mouse_y;
	auto mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y); //<- should be caching this as well 

	if (mouse_state & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)) {
		did_shoot = true;
	}

	if (moveX == 0.0f && moveY == 0.0f && !did_shoot) {
		return InputState(); // empty input
	}
	else {
		InputState input{ moveX, moveY, is_sprinting, mouse_x, mouse_y, did_shoot }; //<- the "x / y" is crazy and (obviously) wont work, but idk what to do
		return input;
	}

}

InputState InputManager::handle_cntrl() {
	return InputState();
}