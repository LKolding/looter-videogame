#pragma once

#include <SDL3/SDL.h>
#include <entt/entt.hpp>

#include "components.hpp"
#include "ECS.hpp"

#include "../common/Animation.hpp"


class EntityFactory {
private:
	ECS* m_engine_pointer;

public:
	EntityFactory(ECS& engine) : m_engine_pointer(&engine) {};

	void spawnPlayerEntity(entt::entity, float x, float y);

};