// engine.hpp : Include file for standard system include files,
// or project specific include files.

#pragma once

// --- System ---
#include <iostream>

// --- EnTT ---
#include <entt/entt.hpp>

// --- SDL3 ---
#include <SDL3/SDL.h>


// Components
#include <components.hpp>

// Systems
#include <Systems/MovementSystem.hpp>

// --- Engine ---
class Engine {
private:
	void init();  // called by constructor

	// EnTT
	entt::registry m_registry;
	std::vector<std::function<void(entt::registry&)>> m_systems;

	// SDL
	const char* m_window_title;
	const int m_window_width;
	const int m_window_height;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

public:
	Engine(const char* title, const int window_width, const int window_height) : m_window_width(window_width), m_window_height(window_height), m_window_title(title)
	{
		this->init();
	}
	SDL_AppResult sdl_init();

	void update();		 // called by AppIterate
	void render();		 // called by AppIterate
	void handle_event(); // called by AppEvent

	SDL_Window* getWindow() const;
	SDL_Renderer* getRenderer() const;
	
	// Custom systems (non-ecs systems)
	// render system
	// audio system


// --- PUBLIC INTERFACE
public:


};
