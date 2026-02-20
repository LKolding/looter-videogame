// engine.hpp : Include file for standard system include files,
// or project specific include files.

#pragma once

// --- System ---
#include <iostream>

// --- EnTT ---
#include <entt/entt.hpp>

// Components
#include "components.hpp"

// Systems
#include "Systems/Physics/VelocitySystem.hpp"
#include "Systems/Physics/PositionSystem.hpp"

#include "Systems/StateSystem.hpp"
#include "Systems/StateAnimationSystem.hpp"

#include "Systems/TextureAnimationSystem.hpp"

// Common
#include "../common/RenderItem.hpp"


/* ECS Engine */
/* 
	(entt wrapper)
	Contains EnTT registry, methods to convert
	Entities into Sprites and systems(tm) 
	to operate on Components, 
*/
class ECS {
private:
	void init_systems();  // called by constructor

	// EnTT registry
	entt::registry m_registry;
	std::vector<std::function<void(entt::registry&, const float dt)>> m_systems;

public:
	ECS()
	{
		this->init_systems();
	}

	void update(const float dt);
	void handle_event();
	void shutdown();

	// Rendering of entities
	auto get_render_items(void) const -> std::vector<RenderItem>;


// --- PUBLIC INTERFACE
public:
	// Movement/transforms
	bool apply_movement(entt::entity e, const glm::vec2 intent);

	// Spawn/destroy
	entt::entity create_entity();
	bool destroy_entity(entt::entity);


	/* EnTT interaction functions (use with caution) */

	entt::registry& get_registry(void);

	template<typename T, typename... Args>
	T& add_component(entt::entity e, Args&&... args) {
		return m_registry.emplace<T>(e, std::forward<Args>(args)...);
	};

	template<typename T>
	bool remove_component(entt::entity e)
	{
		if (!m_registry.any_of<T>(e))
			return false;

		m_registry.remove<T>(e);
		return true;
	}

	template<typename T>
	T* get_component(entt::entity e)
	{
		return m_registry.try_get<T>(e);
	}
};