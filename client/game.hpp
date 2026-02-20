#pragma once

#include "imgui.h"
#include "imgui_impl_sdl3.h"

#include "client.hpp"
#include "ECS.hpp"
#include "../engine/Factory/EntityFactory.hpp"
#include "../engine/components.hpp"


namespace looter
{
    void start_game(ECS& engine, Client& client, EntityFactory& factory);
    void sync_camera_position(ECS& engine, Client& client, entt::entity entity);
}


class Game
{
private:
    ECS engine;
    EntityFactory factory;
    Client client;

public:
    Game()
        : engine()
        , factory(engine)
        , client(static_cast<int>(1920*0.6), static_cast<int>(1080*0.6), "looter")
    { }

    /* called by AppInit */ 
    void init(void)
    {
        looter::start_game(engine, client, factory);
    }
    void logic(float dt);
    bool quit(void);

    bool handle_event(SDL_Event* event);

private:
    void input(float dt);
};