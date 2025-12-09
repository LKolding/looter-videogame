#include <engine.hpp>

// --- Engine ---

// Private
void Engine::init() 
{
	// Add system(s)
	m_systems.push_back(MovementSystem);

}


// Public
bool Engine::sdl_init() {
    // --- SDL3 ---
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer("Looter", m_window_width, m_window_height, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderLogicalPresentation(m_renderer, m_window_width, m_window_height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    return true;
}


void Engine::update() 
{
	for (auto& system : m_systems) {
		system(m_registry);
	}
};

void Engine::render() 
{
    // forEach ( Renderable/ hasComponent<Texture> ): SDL_Render(entity)
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

bool Engine::move_entity(entt::entity e, int dx, int dy) 
{
    get_component<Velocity>(e)->dx = dx;
    get_component<Velocity>(e)->dy = dy;
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
template<typename T, typename... Args>
T& Engine::add_component(entt::entity e, Args&&... args) 
{
    return m_registry.emplace<T>(e, std::forward<Args>(args)...);
}

template<typename T>
bool Engine::remove_component(entt::entity e) 
{
    if (m_registry.remove<T>(e))
        return true;
    else
        return false;
}

template<typename T>
T* Engine::get_component(entt::entity e) 
{
    return &m_registry.get<T>(e);
}