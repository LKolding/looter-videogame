#include "EntityFactory.hpp"


void EntityFactory::spawnPlayerEntity(entt::entity entity, float x, float y) 
{
	using namespace Components;

	// --------------------------
	// ----- Add components -----
	// --------------------------

	auto& pos = this->m_engine_pointer->add_component<Position>(entity, x, y);
	auto& vel = this->m_engine_pointer->add_component<Velocity>(entity);
	auto& mov = this->m_engine_pointer->add_component<MovementIntent>(entity);
	auto& spd = this->m_engine_pointer->add_component<MovementStats>(entity);
	auto& state =this->m_engine_pointer->add_component<State>(entity);
	auto& facing=this->m_engine_pointer->add_component<Facing>(entity);

	auto& tex = this->m_engine_pointer->add_component<AnimatedTexture>(entity);
	tex.id = 1;
	tex.src_rect = { 0, 0, 64, 64 };
	tex.current_frame_index = 0;
	tex.time_passed = 0.0f;

}