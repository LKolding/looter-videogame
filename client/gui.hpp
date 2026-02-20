#pragma once

#include <SDL3/SDL.h>
#include <entt/entt.hpp>

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

#include <vector>

#include "../engine/components.hpp"


// ImGui::Begin
void start_gui_draw(SDL_Window* window, SDL_Renderer* renderer);
// ImGui::End
void end_gui_draw(SDL_Renderer* renderer, const int logical_width, const int logical_height);


// Custom UIs
void draw_positions(SDL_Window* window, SDL_Renderer* renderer, const int logical_width, const int logical_height, std::vector<std::pair<entt::entity, Components::Position>> positions);
void draw_states(SDL_Window* window, SDL_Renderer* renderer, const int logical_width, const int logical_height, std::vector<std::pair<entt::entity, Components::StateComponent&>> states);

// Meta
void draw_view(SDL_Window* window, SDL_Renderer* renderer, const int logical_width, const int logical_height, entt::registry& registry);