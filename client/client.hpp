#pragma once

// Vendor
#include <SDL3/SDL.h>
#include <entt/entt.hpp>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

// My stuff
#include "Managers/ResourceManager.hpp"
#include "Managers/InputManager.hpp"

#include "components.hpp"
#include "../common/RenderItem.hpp"

#include "camera.hpp"
#include "gui.hpp"


class Client 
{
private:
    ResourceManager m_ResourceManager;
    InputManager m_InputManager;

    const int m_logical_render_width  = 960;
    const int m_logical_render_height = 540;
    const char* m_window_title;

public:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    Camera m_camera;

    Client(const int _width, const int _height, const char* wtitle)
        : m_window_title(wtitle)
        , m_camera(m_logical_render_width, m_logical_render_height)
    {
        this->sdl_init(_width, _height);
        this->m_camera.m_position = glm::vec2(0,0);
        this->m_camera.m_zoom = 1.f;
    }
    
    void update(void);
    bool render(std::vector<RenderItem> sprites, entt::registry& registry);

    ResourceManager& get_resource_manager(void);
    InputState get_current_input();

    std::pair<float, float> get_window_scale_factor() const;

private:
    bool render_sprites(std::vector<RenderItem> sprites);
    bool render_ui(entt::registry& registry);
    bool sdl_init(const int _width, const int _height);
};