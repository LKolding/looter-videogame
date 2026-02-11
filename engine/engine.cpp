#include <engine.hpp>

// --- Engine ---

// Private
void Engine::init_systems() 
{
	// Add system(s)
	m_systems.push_back(VelocitySystem);
    m_systems.push_back(TextureAnimationSystem);
}


// Public
void Engine::update(const float dt)
{

    // Iterate through and call all systems
	for (auto& system : m_systems) {
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

std::vector<RenderItem> Engine::get_render_items(void) const {
    std::vector<RenderItem> items;
    // --- Render entities ---
    auto view = m_registry.view<Texture, Position>();
    for (auto entity : view)
    {
        auto& position_component = view.get<Position>(entity);
        auto& texture_component  = view.get<Texture>(entity);

        // Add new RenderItem
        items.push_back({
            .filename = texture_component.filename,
            .source_x = texture_component.src_rect.x,
            .source_y = texture_component.src_rect.y,

            .width = texture_component.src_rect.w,
            .height = texture_component.src_rect.h,
        
            .x = position_component.x,
            .y = position_component.y
        });
    }
    return items;
}


bool Engine::apply_velocity(entt::entity e, float dx, float dy, float multiplier)
{
    if (!m_registry.valid(e))
        return false;

    auto& velocity = m_registry.get<Velocity>(e);

    velocity.dx = dx * multiplier;
    velocity.dy = dy * multiplier;

    return true;
}

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

// func usage: add_component<Transform>(entity, x, y, z); add_component<Health>(entity, 100);
//template<typename T, typename... Args>
//T& Engine::add_component(entt::entity e, Args&&... args) { }

template<typename T>
bool Engine::remove_component(entt::entity e) 
{
    if (m_registry.remove<T>(e))
        return true;
    else
        return false;
}

template<typename T>
T& Engine::get_component(entt::entity e) 
{
    return &m_registry.get<T>(e);
}