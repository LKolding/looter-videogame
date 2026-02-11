// --- SDL3 ---
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

// --- Engine ---
#include "engine.hpp"
#include "client.hpp"

#include "Factory/EntityFactory.hpp"

// --- SDL3 --- callback declarations
SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv);
SDL_AppResult SDL_AppIterate(void* appstate);
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event);
void SDL_AppQuit(void* appstate, SDL_AppResult result);
