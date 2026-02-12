#pragma once

#include "client.hpp"
#include "engine.hpp"
#include "../engine/Factory/EntityFactory.hpp"
#include "../engine/components.hpp"


class Game {
public:
    void init();
    void logic(float dt);
    bool quit(void);
};