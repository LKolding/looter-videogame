// Entry point for the game client (alongside with the engine)

#include "main.hpp"

namespace {

    struct AppData {
        Engine engine = Engine();
        EntityFactory factory{ engine };

        Client client = Client(1920/2, 1080/2, "looter");

        entt::entity player_entity;

        void init_game() {
            this->player_entity = factory.spawnPlayerEntity(100, 100);

        }

    } AppData;
}


// This function should do any one-time startup it requires and then return.
SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) 
{
    SDL_SetAppMetadata("Looter arcade", "1.0", "com.lkolding.looter");

    // if (!AppData.client.sdl_init())
    //     return SDL_APP_FAILURE;

    AppData.init_game();

    return SDL_APP_CONTINUE; /* Carry on */
}


// This is called over and over, possibly at the refresh rate of the display or some other metric that the platform dictates
// You do not check the event queue in this function (SDL_AppEvent exists for that)
SDL_AppResult SDL_AppIterate(void* appstate)
{
    // Calculate delta time
    static unsigned int lastTime = lastTime ? lastTime : 0;
    unsigned int currentTime = SDL_GetTicks();
    const uint32_t deltaTime = currentTime - lastTime;
    lastTime = currentTime; // ??? isn't this correct

    // Update engine & client
    AppData.engine.update(deltaTime);
    AppData.client.update();

    // Render
    AppData.client.render(AppData.engine.get_render_items());

    // add imgui here maybe

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}


// This will be called whenever an SDL event arrives.
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        AppData.engine.shutdown();
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}


// This is called once before terminating the app--assuming the app isn't being forcibly killed or crashed--as a last chance to clean up.
// The SDL_AppResult value that terminated the app is provided here, in case it's useful to know if this was a successful or failing run of the app.
void SDL_AppQuit(void* appstate, SDL_AppResult result) 
{
    /* SDL will clean up the window/renderer for us. */
}