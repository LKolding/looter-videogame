#pragma once

#include <SDL3/SDL.h>
#include <entt/entt.hpp>

#include "components.hpp"
#include "engine.hpp"  // for .createEntity()

#include "../common/AnimationClip.hpp"


class EntityFactory {
private:
	Engine* m_engine_pointer;

public:
	EntityFactory(Engine& engine) : m_engine_pointer(&engine) {};

	entt::entity spawnPlayerEntity(entt::entity, float x, float y);

};