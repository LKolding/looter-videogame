#include "game.hpp"


namespace looter
{
    struct data
    {
        Engine engine{};
        EntityFactory factory{ engine };
        Client client{static_cast<int>(1920*0.6), static_cast<int>(1080*0.6), "looter"};

        entt::entity player_entity;

    } GameData;

    void start_game()
        {
            // Get entity handle
            auto entity = GameData.engine.create_entity();
            GameData.player_entity = GameData.factory.spawnPlayerEntity(entity, 100, 100);

            // Get texture (for its ID)
            Components::AnimatedTexture* texture_component = GameData.engine.get_component<Components::AnimatedTexture>(entity);
            if (!texture_component)
            {
                return;
            }

            // Get animation set
            AnimationSet* animation_set = GameData.client.get_texture_manager().getAnimationSet(texture_component->id);
            if (!animation_set)
            {
                return;
            }
            
            // Apply
            auto& animation_clip_reference = animation_set->animations.at(1);
            GameData.engine.add_component<Components::AnimationClipReference>(entity, animation_clip_reference);
            GameData.engine.add_component<Components::AnimationSetsReference>(entity, GameData.client.get_texture_manager().getAnimationSets());

        }

    void update_player_input()
    {
        InputState input = GameData.client.get_current_input();
        GameData.engine.apply_movement(GameData.player_entity, input.moveX, input.moveY);
    }
}


void Game::init()
{
    looter::start_game();
}


void Game::logic(float dt) 
{
    using namespace looter;

    // Update engine & client
    GameData.engine.update(dt);
    GameData.client.update();

    // Input behavior
    update_player_input();

    // Render
    GameData.client.render(GameData.engine.get_render_items());

    // add imgui here maybe

}


bool Game::quit(void)
{
    looter::GameData.engine.shutdown();
    return true;
}