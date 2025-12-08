#include <engine.hpp>

// --- Engine ---

// Private
void Engine::init() 
{
	// Add system(s)
	m_systems.push_back(MovementSystem);

}


// Public
SDL_AppResult Engine::sdl_init() {
    // --- SDL3 ---
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Looter", m_window_width, m_window_height, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(m_renderer, m_window_width, m_window_height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

}


void Engine::update() 
{
	for (auto& system : m_systems) {
		system(m_registry);
	}
};
void Engine::render() {};
void Engine::handle_event() {};

// Public interface
SDL_Window* Engine::getWindow() const {
	return m_window;
}
SDL_Renderer* Engine::getRenderer() const {
	return m_renderer;
}