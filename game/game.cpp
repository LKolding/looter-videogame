#include "game.hpp"


namespace {

    #define WINDOW_WIDTH 640
    #define WINDOW_HEIGHT 480

    struct AppData {
        Engine engine = Engine("Looter", WINDOW_WIDTH, WINDOW_HEIGHT);

        void game_logic() {

        }
    } AppData;
}


// This function should do any one-time startup it requires and then return.
SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) 
{
    SDL_SetAppMetadata("Looter arcade", "1.0", "com.lkolding.looter");

    if (!AppData.engine.sdl_init())
        return SDL_APP_FAILURE;

    return SDL_APP_CONTINUE; /* Carry on */
}


// This is called over and over, possibly at the refresh rate of the display or some other metric that the platform dictates
// You do not check the event queue in this function (SDL_AppEvent exists for that)
SDL_AppResult SDL_AppIterate(void* appstate)
{

    AppData.engine.update();
    AppData.engine.render();

    AppData.game_logic();

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