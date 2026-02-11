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

#include "../common/RenderItem.hpp" // ????


// --- Engine ---
class Engine {
private:
	void init_systems();  // called by constructor

	// EnTT
	entt::registry m_registry;
	std::vector<std::function<void(entt::registry&, const float dt)>> m_systems;

public:
	Engine()
	{
		this->init_systems();
	}

	void update(const float dt);// called by AppIterate
	void handle_event();		// called by AppEvent
	void shutdown();			// called by AppQuit

	// Rendering of internal entities
	std::vector<RenderItem> get_render_items(void) const;

// --- PUBLIC INTERFACE
public:

	// Movement/transforms
	bool apply_velocity(entt::entity e, float dx, float dy, float multiplier = 1.0f);

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
