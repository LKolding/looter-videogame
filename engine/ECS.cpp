#include <ECS.hpp>

// Private

void ECS::init_systems() 
{
	// Add system(s)
	m_systems.push_back(VelocitySystem);
    m_systems.push_back(PositionSystem);
    m_systems.push_back(StateSystem);
    m_systems.push_back(AnimationSystem);
    m_systems.push_back(AnimationTimeSystem);
}

// Public

void ECS::update(const float dt)
{
    // Iterate through and call all systems
	for (auto& system : m_systems)
    {
		system(m_registry, dt);
	}
};

void ECS::handle_event() 
{
    // Input handling
};

void ECS::shutdown() 
{
    // Save logic goes here
};


// --- Public interface ---

entt::registry& ECS::get_registry(void)
{
    return m_registry;
}

// Construct renderable items from texture.id, position etc.
auto ECS::get_render_items(void) const -> std::vector<RenderItem>
{
    std::vector<RenderItem> items;
    
    using namespace Components;

    // AnimatedTexture
    auto view = m_registry.view<AnimatedTexture, Position>();
    for (auto [entity, texture, position]: view.each())
    {
        if (m_registry.all_of<Facing>(entity))
        {
            auto &facing = m_registry.get<Facing>(entity);
            items.push_back({
                .id = texture.id,
                .source_x = texture.src_rect.x,
                .source_y = texture.src_rect.y,
        
                .width  = texture.src_rect.w,
                .height = texture.src_rect.h,
            
                .x = position.x,
                .y = position.y,
                .facing = facing.value
            });
        } 
        else 
        {
            items.push_back({
                .id = texture.id,
                .source_x = texture.src_rect.x,
                .source_y = texture.src_rect.y,
        
                .width  = texture.src_rect.w,
                .height = texture.src_rect.h,
            
                .x = position.x,
                .y = position.y,
            });
        }
    }

    return items;
}

// Interface to MovementIntent component
bool ECS::apply_movement(entt::entity e, const glm::vec2 intent)
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

entt::entity ECS::create_entity() 
{
    return m_registry.create();
}

bool ECS::destroy_entity(entt::entity e) 
{
    if (m_registry.destroy(e))
        return true;
    else
        return false;
}
