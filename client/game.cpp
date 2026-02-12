#include "game.hpp"


namespace looter
{

    struct data
    {
        Engine engine{};
        EntityFactory factory{ engine };
        Client client{static_cast<int>(1920*0.6), static_cast<int>(1080*0.6), "looter"};

        entt::entity player_entity;

        void init_game()
        {
            this->player_entity = factory.spawnPlayerEntity(100, 100);
        }

        void update_player_input()
        {
            InputState input = client.get_current_input();
            engine.apply_movement(player_entity, input.moveX, input.moveY);
        }

    } GameData;
}


void Game::init()
{
    looter::GameData.init_game();
}


void Game::logic(float dt) 
{
    using namespace looter;

    // Update engine & client
    GameData.engine.update(dt);
    GameData.client.update();

    // Input behavior
    GameData.update_player_input();

    // Render
    GameData.client.render(GameData.engine.get_render_items());

    // add imgui here maybe
}


bool Game::quit(void)
{
    looter::GameData.engine.shutdown();
    return true;
}