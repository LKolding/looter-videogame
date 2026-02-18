#include "game.hpp"


void Game::start_game(void)
{
    // Get entity handle
    player_entity = engine.create_entity();
    factory.spawnPlayerEntity(player_entity, 0, 0);

    // Get texture (for its ID)
    Components::AnimatedTexture* texture_component = engine.get_component<Components::AnimatedTexture>(player_entity);
    if (!texture_component)
        return;
    
    // In order to properly initialize a sprite with an
    // AnimatedTexture, I need to retrieve a reference to
    // the actual AnimationClip data (stored in TextureManager).

    // Get animation set
    AnimationSet* set_ptr = client.get_texture_manager().getAnimationSet(texture_component->id);
    if (!set_ptr)
        return;

    // Get reference to AnimationClip
    auto& clipRef = set_ptr->animations.at(1);
    
    // Apply
    engine.add_component<Components::AnimationClipReference>(player_entity, clipRef);
    engine.add_component<Components::AnimationSetsReference>(player_entity, client.get_texture_manager().getAnimationSets());
}


void Game::logic(float dt) 
{
    // Input behavior
    input(dt);

    // Update engine & client
    engine.update(dt);
    client.update();

    // Render
    client.render(engine.get_render_items());

    // TEMP
    // Sync player and camera
    auto *ppos = engine.get_component<Components::Position>(player_entity);
    client.m_camera.m_position.x = ppos->x;
    client.m_camera.m_position.y = ppos->y;

    // add imgui here maybe

}


bool Game::quit(void)
{
    engine.shutdown();
    return true;
}


// -------------------
// ----- Private -----
// -------------------

void Game::input(float dt)
{
    InputState input = client.get_current_input();

    // Camera movement
    // client.m_camera.m_position.x += input.moveX * 100.0f * dt;
    // client.m_camera.m_position.y += input.moveY * 100.0f * dt;

    // Player movement
    if (input.move_intent.length() > 0.0f)
        engine.apply_movement(player_entity, input.move_intent);
}