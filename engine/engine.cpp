#include <engine.hpp>

// --- Engine ---

// Private
void Engine::init() 
{
	// Add system(s)
	m_systems.push_back(VelocitySystem);
    m_systems.push_back(TextureAnimationSystem);

}


// Public
bool Engine::sdl_init() {
    // --- SDL3 ---
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer("Looter", m_window_width, m_window_height, NULL, &m_window, &m_renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderLogicalPresentation(m_renderer, m_window_width, m_window_height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // Texture manager
    this->textureManager = std::make_unique<TextureManager>(this->m_renderer);
    if (!this->textureManager->load_textures()) {
        std::cout << "Couldn't load textures\n";
        return false;
    }

    return true;
}

void Engine::player_input() {
    // Get keystate of relavant keys
    // Flag behavior (eg. isMovingRight) ?
    // Dispatch events?
    // 
}

void Engine::update(const float dt)
{
    // Iterate through and call all systems
	for (auto& system : m_systems) {
		system(m_registry, dt);
	}
};

void Engine::render() 
{
    SDL_RenderClear(m_renderer);
    
    auto view = m_registry.view<Texture, Position>();
    for (auto entity : view)
    {
        auto& position_component = view.get<Position>(entity);
        auto& texture_component  = view.get<Texture>(entity);

        const float x_offset = texture_component.src_rect.w / 2;
        const float y_offset = texture_component.src_rect.h / 2;

        const SDL_FRect *src_rect= &texture_component.src_rect;
        const SDL_FRect dst_rect = { position_component.x - x_offset, position_component.y - y_offset, texture_component.src_rect.w, texture_component.src_rect.h };

        // Check if texture is valid
        SDL_Texture* texture = this->textureManager->getTexture(texture_component.id);
        if (!texture) {
            std::cout << "Error: couldn't get pointer to texture with id: " << texture_component.id << "\n";
            continue;
        }
        
        SDL_RenderTexture(
            m_renderer,
            texture,
            src_rect,
            &dst_rect
        );
    }
    // Show renditions (?)
    SDL_RenderPresent(m_renderer);
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

bool Engine::apply_velocity(entt::entity e, float dx, float dy)
{
    auto& velocity = m_registry.get<Velocity>(e);
    velocity.dx = dx;
    velocity.dy = dy;

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