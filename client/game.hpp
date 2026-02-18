#pragma once


#include "client.hpp"
#include "engine.hpp"
#include "../engine/Factory/EntityFactory.hpp"
#include "../engine/components.hpp"


class Game
{
private:
    Engine engine;
    EntityFactory factory;
    Client client;

    entt::entity player_entity;

public:
    Game()
        : engine()
        , factory(engine)
        , client(static_cast<int>(1920*0.6), static_cast<int>(1080*0.6), "looter")
    { }

    void start_game(void);
    void logic(float dt);
    bool quit(void);

private:
    void input(float dt);
};