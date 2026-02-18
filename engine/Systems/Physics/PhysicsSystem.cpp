#include "PhysicsSystem.hpp"

// Engine owns b2World
// PhysicsSystem steps it
// PhysicsSystem syncs back to registry
// Everything else reads from registry

// Authority-wise:
// Dynamic objects -> Box2D is authoritative.
// Static or non-physics entities -> only have Position

// That means Box2D can handle:
// Collision detection
// Collision resolution
// Sliding along walls
// Sensors / triggers
// Continuous collision detection (bullets)
// Friction and restitution



void PhysicsSystem(entt::registry& registry, const float dt) 
{

}