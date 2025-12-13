// engine.hpp : Include file for standard system include files,
// or project specific include files.

#pragma once

// --- System ---
#include <iostream>

// --- EnTT ---
#include <entt/entt.hpp>

// --- SDL3 ---
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>


// Components
#include <components.hpp>

// Systems
#include <Systems/VelocitySystem.hpp>
#include <Systems/TextureAnimationSystem.hpp>

// Managers
#include <Managers/TextureManager.hpp>


// --- Engine ---
class Engine {
private:
	void init();  // called by constructor

	// EnTT
	entt::registry m_registry;
	std::vector<std::function<void(entt::registry&, const float dt)>> m_systems;

	// SDL
	const char* m_window_title;
	const int m_window_width;
	const int m_window_height;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	// Engine
	//TextureManager* textureManager;
	std::unique_ptr<TextureManager> textureManager;

public:
	Engine(const char* title, const int window_width, const int window_height) : 
		m_window_width(window_width), 
		m_window_height(window_height), 
		m_window_title(title)
	{
		this->init();
	}
	bool sdl_init();

	void player_input();		// called by AppEvent (when new input registers)
	void update(const float dt);// called by AppIterate
	void render();				// called by AppIterate
	void handle_event();		// called by AppEvent
	void shutdown();			// called by AppQuit

	// Custom systems (non-ecs systems)
	// render system
	// audio system


// --- PUBLIC INTERFACE
public:

	// Movement/transforms
	bool apply_velocity(entt::entity e, float dx, float dy);

	// Spawn/destroy
	entt::entity create_entity();
	bool destroy_entity(entt::entity);


	// Entity Factory functions (use with caution)
	template<typename T, typename... Args>
	T& add_component(entt::entity e, Args&&... args) {
		return m_registry.emplace<T>(e, std::forward<Args>(args)...);
	};

	template<typename T>
	bool remove_component(entt::entity e);

	template<typename T>
	T& get_component(entt::entity e);

};
