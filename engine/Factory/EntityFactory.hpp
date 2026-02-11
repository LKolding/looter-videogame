#pragma once

#include <filesystem>

#include <SDL3/SDL.h>
#include <entt/entt.hpp>

#include "components.hpp"
#include "engine.hpp"  // for createEntity()


class EntityFactory {
private:
	Engine* m_engine_pointer;

public:
	EntityFactory(Engine& engine) : m_engine_pointer(&engine) {};

	entt::entity spawnPlayerEntity(float x, float y);

};