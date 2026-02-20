#pragma once
#include <entt/entt.hpp>
#include <cmath>
#include <glm/glm.hpp>

#include "components.hpp"
#include "../common/types.hpp"


void VelocitySystem(entt::registry& registry, const float dt);