#include "client.hpp"

/* --- Public --- */

bool Client::update(void) 
{
    m_inputManager->update();
}

/* --- Private --- */

bool Client::sdl_init(void) 
{
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

    // Texture manager
    m_textureManager->register_renderer(m_renderer);
    if (m_textureManager->load_textures()) 
    {
        std::cout << "Couldn't load textures\n";
        return false;
    }

    return true;
}

bool Client::render(std::vector<RenderItem> items) 
{
    // Background
    SDL_SetRenderDrawColorFloat(m_renderer, 210.0f, 110.0f, 130.0f, 255.0f);
    SDL_RenderClear(m_renderer);

    // Iterate renderables
    for (auto item : items) 
    {
        // Check if texture is valid
        SDL_Texture* texture = m_textureManager->getTexture(item.filename);
        if (!texture) {
            std::cout << "Error: couldn't get pointer to texture with filename: " << item.filename << "\n";
            continue;
        }

        const float x_offset = item.width  / 2;
        const float y_offset = item.height / 2;

        const SDL_FRect src_rect { item.source_x, item.source_y, item.width, item.height };
        const SDL_FRect dst_rect { item.x - x_offset, item.y - y_offset, item.width, item.height };

        // Render
        SDL_RenderTexture(m_renderer, texture, &src_rect, &dst_rect);
    }

    // Show renditions (?)
    SDL_RenderPresent(m_renderer);
    return true;
}
