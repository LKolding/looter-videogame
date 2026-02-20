#include "main.hpp"


struct AppData
{
    Game game;

    // Calculates and returns delta time
    const float get_deltaTime(void)
    {
        static Uint64 last = SDL_GetPerformanceCounter();

        Uint64 current = SDL_GetPerformanceCounter();

        float dt = (current - last) /
            (float)SDL_GetPerformanceFrequency();

        last = current;

        if (dt > 0.033f)
            dt = 0.033f;

        return dt;
    }
};


// This function should do any one-time startup it requires and then return.
SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) 
{
    *appstate = new AppData{};
    auto* data = static_cast<AppData*>(*appstate);
    SDL_SetAppMetadata("Looter arcade", "1.0", "com.lkolding.looter");
    data->game.init();
    return SDL_APP_CONTINUE; /* carry on */
}


// This is called over and over, possibly at the refresh rate of the display or some other metric that the platform dictates
// You do not check the event queue in this function (SDL_AppEvent exists for that)
SDL_AppResult SDL_AppIterate(void* appstate)
{
    auto* data = static_cast<AppData*>(appstate);
    data->game.logic(data->get_deltaTime());
    return SDL_APP_CONTINUE;  /* carry on */
}


// This will be called whenever an SDL event arrives.
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    auto* data = static_cast<AppData*>(appstate);

    data->game.handle_event(event);

    if (event->type == SDL_EVENT_QUIT) {
        if (!data->game.quit())
            return SDL_APP_FAILURE;
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on */
}


// This is called once before terminating the app--assuming the app isn't being forcibly killed or crashed--as a last chance to clean up.
// The SDL_AppResult value that terminated the app is provided here, in case it's useful to know if this was a successful or failing run of the app.
void SDL_AppQuit(void* appstate, SDL_AppResult result) 
{
    /* SDL will clean up the window/renderer for us. */
    delete static_cast<AppData*>(appstate);
}