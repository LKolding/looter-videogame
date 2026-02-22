#include "client.hpp"


/* --- Private --- */

bool Client::sdl_init(const int _width, const int _height) 
{
    /* SDL */
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer("Looter", _width, _height, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderLogicalPresentation(m_renderer, m_logical_render_width, m_logical_render_height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    /* ImGUI */

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // Something(?)
    ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer);
    ImGui_ImplSDLRenderer3_Init(m_renderer);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark(); //ImGui::StyleColorsLight();
    // Setup scaling
    // ImGuiStyle& style = ImGui::GetStyle();
    // style.ScaleAllSizes(0.6f);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    
    /* Resource Manager */
    m_ResourceManager.register_renderer(m_renderer);
    m_ResourceManager.init();
    
    return true;
}    

bool Client::render_ui(entt::registry& registry)
{
    /* ImGUI */
    draw_view(m_window, m_renderer, m_logical_render_width, m_logical_render_height, registry);
    return true;
}

bool Client::render_sprites(std::vector<RenderItem> sprites)
{
    // Iterate renderables
    for (auto sprite : sprites)
    {
        
        // Check if texture is valid
        SDL_Texture* texture = m_ResourceManager.getTexture(sprite.id);
        if (!texture)
        {
            std::cout << "Error: Texture with id " << sprite.id << " does not exist.\n";
            continue;
        }    

        const float height = sprite.height * 2.f;
        const float width  = sprite.width  * 2.f;

        // Offset x & y by texture size * 0.5
        const float x_offset = width * 0.5f;
        const float y_offset = height* 0.5f;

        // Apply offset
        const float x = sprite.x - x_offset;
        const float y = sprite.y - y_offset;

        // Convert from world to screen space (camera)
        glm::vec2 screen_position = m_camera.world_to_screen(glm::vec2(x,y));
        screen_position = glm::round(screen_position); // "pixel art rounding" (?)

        // Calculate source rectangle
        const SDL_FRect src_rect { sprite.source_x, sprite.source_y, sprite.width, sprite.height };

        // Destination rectangle
        const SDL_FRect dst_rect { screen_position.x, screen_position.y, width, height };


        /* -- Render -- */

        SDL_RenderTexture(m_renderer, texture, &src_rect, &dst_rect);

        // "Hitbox"
        SDL_SetRenderDrawColorFloat(m_renderer, 0.0f, 1.0f, 0.0f, 1.0f);
        SDL_RenderRect(m_renderer, &dst_rect);
    }    
    return true;
}    


/* --- Public --- */

void Client::update(void) 
{
    m_InputManager.update();
}    

bool Client::render(std::vector<RenderItem> sprites, entt::registry& registry)
{
    // Background
    SDL_SetRenderDrawColorFloat(m_renderer, 0.2f, 0.2f, 0.2f, 1.0f);
    SDL_RenderClear(m_renderer);

    this->render_sprites(sprites);
    this->render_ui(registry);

    /* Apply renditions */
    SDL_RenderPresent(m_renderer);
    return true;
}    


ResourceManager& Client::get_resource_manager(void)
{
    return m_ResourceManager;
}

InputState Client::get_current_input()
{
    return m_InputManager.get_input_state();
}

std::pair<float, float> Client::get_window_scale_factor() const
{
    int w, h;
    SDL_GetRenderOutputSize(this->m_renderer, &w, &h);

    float scale_x = this->m_logical_render_width  / w;
    float scale_y = this->m_logical_render_height / h;

    return std::make_pair(scale_x, scale_y);
}