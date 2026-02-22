#include "gui.hpp"


/* To begin with, one must call this */
void start_gui_draw(SDL_Window* window, SDL_Renderer* renderer)
{
    // Switch to window space for ImGui
    SDL_SetRenderLogicalPresentation(renderer, 0, 0, SDL_LOGICAL_PRESENTATION_DISABLED);
    // Update DisplaySize to window size
    int win_w, win_h;
    SDL_GetWindowSize(window, &win_w, &win_h);
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)win_w, (float)win_h);

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Debug");
}
/* Afterwards you draw whatever, and call this function to end */
void end_gui_draw(SDL_Renderer* renderer, const int logical_width, const int logical_height)
{
    ImGui::End();
    // Render ImGui
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
    // Switch back to logical presentation for game
    SDL_SetRenderLogicalPresentation(renderer, logical_width, logical_height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}


void draw_view(SDL_Window* window, SDL_Renderer* renderer, const int logical_width, const int logical_height, entt::registry& registry)
{
    /* Init ImGui */
    start_gui_draw(window, renderer);


    const int PANEL_SIZE = 80;

    /* Positions */
    ImGui::TextColored(ImVec4(1,1,0,1), "Position");
    ImGui::BeginChild("Position", ImVec2(0, PANEL_SIZE), true);
    auto view2 = registry.view<Components::Position>();
    for (auto [entity, position] : view2.each())
    {
        ImGui::Text("%i | (%0.f, %0.f)", entity, position.x, position.y);
    }
    ImGui::EndChild();

    /* Velocity */
    ImGui::TextColored(ImVec4(1,1,0,1), "Velocity");
    ImGui::BeginChild("Velocity", ImVec2(0, PANEL_SIZE), true);
    auto view5 = registry.view<Components::Velocity>();
    for (auto [entity, velocity] : view5.each())
    {
        ImGui::Text("%i | (%0.f, %0.f)", entity, velocity.value.x, velocity.value.y);
    }
    ImGui::EndChild();

    /* Facing */
    ImGui::TextColored(ImVec4(1,1,0,1), "Facing");
    ImGui::BeginChild("Facing", ImVec2(0, PANEL_SIZE), true);
    auto view3 = registry.view<Components::Facing>();
    for (auto [entity, facing] : view3.each())
    {
        ImGui::Text("%i | %s", entity, facing.to_string().c_str());
    }
    ImGui::EndChild();


    /* AnimationData */
    ImGui::TextColored(ImVec4(1,1,0,1), "Animation/texture");
    ImGui::BeginChild("AnimationData", ImVec2(0, PANEL_SIZE), true);
    auto view4 = registry.view<Components::AnimatedTexture, Components::AnimationClipReference>();
    for (auto [entity, texture, data] : view4.each())
    {
        ImGui::Text("%i | Frame: %i/%zu | id: %i", entity, texture.current_frame_index, data.ref->frames.size(), texture.id);
        ImGui::Text("%i | Frame: (%i, %i)", entity, data.ref->frames.at(texture.current_frame_index).x, data.ref->frames.at(texture.current_frame_index).y);
        // ImGui::Text("%x", data.ref);
    }
    ImGui::EndChild();


    /* Apply renditions (ImGui) */
    end_gui_draw(renderer, logical_width, logical_height);
}