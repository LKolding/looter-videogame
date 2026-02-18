#include <engine.hpp>

// Private

void Engine::init_systems() 
{
	// Add system(s)
	m_systems.push_back(VelocitySystem);
    m_systems.push_back(PositionSystem);
    m_systems.push_back(StateSystem);
    m_systems.push_back(StateAnimationSystem);
    m_systems.push_back(TextureAnimationSystem);
}

// Public

void Engine::update(const float dt)
{
    // Iterate through and call all systems
	for (auto& system : m_systems)
    {
		system(m_registry, dt);
	}
};

void Engine::handle_event() 
{
    // Input handling
};

void Engine::shutdown() 
{
    // Save logic goes here
};


// --- Public interface ---

// Construct renderable items from texture.id, position etc.
std::vector<RenderItem> Engine::get_render_items(void)
{
    std::vector<RenderItem> items;
    
    using namespace Components;

    // AnimatedTexture
    auto view = m_registry.view<AnimatedTexture, Position>();
    for (auto [entity, texture, position]: view.each())
    {
        // Add new RenderItem
        items.push_back({
            .id = texture.id,
            .source_x = texture.src_rect.x,
            .source_y = texture.src_rect.y,
    
            .width  = texture.src_rect.w,
            .height = texture.src_rect.h,
        
            .x = position.x,
            .y = position.y
        });
    }
    return items;

    // Texture
    // auto view = m_registry.view<Texture, Position>();
    // for (auto [entity, texture, position]: view.each())
    // {
    //     // Add new RenderItem
    //     items.push_back({
    //         .id = texture.id,
    //         .source_x = texture.src_rect.x,
    //         .source_y = texture.src_rect.y,
    
    //         .width  = texture.src_rect.w,
    //         .height = texture.src_rect.h,
        
    //         .x = position.x,
    //         .y = position.y
    //     });
    // }

}

// Interface to MovementIntent component
bool Engine::apply_movement(entt::entity e, const glm::vec2 intent)
{
    if (!m_registry.valid(e))
        return false;
    
    using namespace Components;

    // Get reference to MovementIntent component
    MovementIntent* movement = m_registry.try_get<MovementIntent>(e);
    if (!movement)
        return false;

    // Update it
    movement->value = intent;

    return true;
}


/* Entity creation/destruction */

entt::entity Engine::create_entity() 
{
    return m_registry.create();
}

bool Engine::destroy_entity(entt::entity e) 
{
    if (m_registry.destroy(e))
        return true;
    else
        return false;
}
