#include "EntityFactory.hpp"


#define LINK_SPRITESHEET_FILENAME "link_spritesheet.png"
const std::filesystem::path texture_filename_and_path = std::filesystem::path("assets") / "textures";

using namespace Components;

entt::entity EntityFactory::spawnPlayerEntity(float x, float y) 
{
	// Get entity handle
	auto entity = this->m_engine_pointer->create_entity();

	// Add components
	auto& pos = this->m_engine_pointer->add_component<Position>(entity);
	pos.x = x;
	pos.y = y;

	auto& vel = this->m_engine_pointer->add_component<Velocity>(entity);
	vel.speed = 0.2f;
	vel.dx = 0.0f;
	vel.dy = 0.0f;

	auto& tex = this->m_engine_pointer->add_component<Texture>(entity);
	tex.filename = "link_spritesheet.png";
	tex.src_rect = { 0, 0, 120, 130 };

	auto& anim = this->m_engine_pointer->add_component<TextureAnimation>(entity);
	anim.total_frames = 3;
	anim.frame_time = 1000/10;
	anim.current_animation = 4;  // basically the y coord (tex.h*this)
	anim.current_frame_index = 0;// and the x coord (tex.w*this)
	anim.time_passed = 0.0f;

	// Return entity handle upon success
	return entity;

}