#include "client.hpp"


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
    m_textureManager.register_renderer(m_renderer);
    m_textureManager.init();

    return true;
}


/* --- Public --- */


void Client::update(void) 
{
    m_inputManager->update();
}


bool Client::render(std::vector<RenderItem> items) 
{
    // Background
    SDL_SetRenderDrawColorFloat(m_renderer, 0.2f, 0.2f, 0.2f, 1.0f);
    SDL_RenderClear(m_renderer);

    // Iterate renderables
    for (auto item : items)
    {
        // Check if texture is valid
        SDL_Texture* texture = m_textureManager.getTexture(item.id);
        if (!texture)
        {
            std::cout << "Error: Texture with id " << item.id << " does not exist.\n";
            continue;
        }

        // temp
        const float SCALE_MULT = 4;

        // Offset x & y by texture size * 0.5
        const float x_offset = item.width*SCALE_MULT  * 0.5;
        const float y_offset = item.height*SCALE_MULT * 0.5;

        const SDL_FRect src_rect { item.source_x, item.source_y, item.width, item.height };
        const SDL_FRect dst_rect { item.x - x_offset, item.y - y_offset, item.width*SCALE_MULT, item.height*SCALE_MULT };

        // Render
        SDL_RenderTexture(m_renderer, texture, &src_rect, &dst_rect);

        // TEMP
        // Render text
        // SDL_SetRenderDrawColorFloat(m_renderer, 1.0f, 0.0f, 0.0f, 1.0f);
        // SDL_RenderDebugText(m_renderer, item.x, item.y-y_offset, "UwU");
    }

    // Show renditions (?)
    SDL_RenderPresent(m_renderer);
    return true;
}

TextureManager& Client::get_texture_manager(void)
{
    return m_textureManager;
}

InputState Client::get_current_input()
{
    return m_inputManager->get_input_state();
}