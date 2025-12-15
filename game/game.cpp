#include "game.hpp"


namespace {

    #define WINDOW_WIDTH  1920 / 2
    #define WINDOW_HEIGHT 1080 / 2

    struct AppData {
        Engine engine = Engine("Looter", WINDOW_WIDTH, WINDOW_HEIGHT);
        EntityFactory factory{ engine };

        void init_game() {
            factory.spawnPlayerEntity(100, 100);

        }

        void game_logic() {
            // --- game rules...
            //
            // collection of functions operating on (Engine& e) ?
            // Here lives game data that is not "interating" with
            // game/engine entities, components, systems etc.
        
                // TODO
            // Seperate logic into a struct or smth to have this
            // file only (mainly) be the sdl callback definitions
            
        }
    } AppData;
}


// This function should do any one-time startup it requires and then return.
SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) 
{
    SDL_SetAppMetadata("Looter arcade", "1.0", "com.lkolding.looter");

    if (!AppData.engine.sdl_init())
        return SDL_APP_FAILURE;

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

    AppData.engine.player_input();

    AppData.game_logic();

    AppData.engine.update(deltaTime);
    AppData.engine.render();

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