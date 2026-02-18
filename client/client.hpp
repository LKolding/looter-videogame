#pragma once

// Vendor
#include <SDL3/SDL.h>
#include <iostream>
// My stuff
#include "Managers/TextureManager.hpp"
#include "Managers/InputManager.hpp"

#include "components.hpp"
#include "../common/RenderItem.hpp"

#include "camera.hpp"


class Client 
{
private:
    TextureManager m_textureManager;
    InputManager m_inputManager;

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
    }
    
    void update(void);
    bool render(std::vector<RenderItem> items);

    // Managers
    TextureManager& get_texture_manager(void);

    // Input
    InputState get_current_input();

private:
    bool sdl_init(const int _width, const int _height);
};