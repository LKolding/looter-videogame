#pragma once

// Vendor
#include <SDL3/SDL.h>
#include <iostream>
// My stuff
#include "Managers/TextureManager.hpp"
#include "Managers/InputManager.hpp"

#include "components.hpp"
#include "../common/RenderItem.hpp"


class Client {
private:
    TextureManager m_textureManager;

    std::unique_ptr<InputManager> m_inputManager = std::make_unique<InputManager>();

public:
    const int m_window_width;
    const int m_window_height;
    const char* m_window_title;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

public:
    Client(const int wwidth, const int wheight, const char* wtitle) :
        m_window_width(wwidth),
        m_window_height(wheight),
        m_window_title(wtitle) 
    {
        this->sdl_init(); 
    }
    
    void update(void);
    bool render(std::vector<RenderItem> items);

    // Managers
    TextureManager& get_texture_manager(void);

    // Input
    InputState get_current_input();

private:
    bool sdl_init(void);
};