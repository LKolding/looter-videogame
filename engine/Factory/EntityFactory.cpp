#include "EntityFactory.hpp"
#include "components.hpp"

bool EntityFactory::spawnPlayerEntity(float x, float y) {
	// Return false if engine is dead (for some reason?
	if (!this->m_engine_pointer)
		return false;

	// Get entity handle
	auto entity = this->m_engine_pointer->create_entity();

	// Add components
	auto& pos = this->m_engine_pointer->add_component<Position>(entity);
	pos.x = x;
	pos.y = y;

	auto& tex = this->m_engine_pointer->add_component<Texture>(entity);
	tex.id = 1;
	tex.src_rect = { 0, 0, 120, 120 };

	auto& anim = this->m_engine_pointer->add_component<TextureAnimation>(entity);
	anim.total_frames = 3;
	anim.frame_time = 999;
	anim.current_frame_index = 0;
	anim.time_passed = 0.0f;

	// Return true upon success
	return true;

}