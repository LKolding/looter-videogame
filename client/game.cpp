#include "game.hpp"

// temp
entt::entity spawn_player_entity(ECS& engine, Client& client, EntityFactory& factory)
{
    // Get entity handle
    auto player_entity = engine.create_entity();
    factory.spawnPlayerEntity(player_entity, 0, 0);

    // Get texture (for its ID)
    Components::AnimatedTexture* texture_component = engine.get_component<Components::AnimatedTexture>(player_entity);
    if (!texture_component)
    {
        std::runtime_error("Texture missing!");
    }
    
    // Get animation set
    AnimationSet* set_ptr = client.get_resource_manager().getAnimationSet(texture_component->id);
    if (!set_ptr)
    {
        std::runtime_error("AnimationSet missing!");
    }

    // Get ptr to AnimationClip
    AnimationClip* clipRef = &set_ptr->_animations.at(Direction::North);
    
    // Apply
    engine.add_component<Components::AnimationClipReference>(player_entity, clipRef);
    engine.add_component<Components::AnimationSetsReference>(player_entity, client.get_resource_manager().getAnimationSets());

    return player_entity;
}


// ---------------------
// ----- namespace -----
// ---------------------

namespace looter
{
    entt::entity player_entity;
}

void looter::sync_camera_position(ECS& engine, Client& client, entt::entity entity)
{
    // TEMP
    // Sync player entity and camera
    auto *ppos = engine.get_component<Components::Position>(entity);
    if (ppos)
    {
        client.m_camera.m_position.x = ppos->x;
        client.m_camera.m_position.y = ppos->y;
    }
}

void looter::start_game(ECS& engine, Client& client, EntityFactory& factory)
{
    player_entity = spawn_player_entity(engine, client, factory);
    spawn_player_entity(engine, client, factory);
}


// ----------------
// ----- Game -----
// ----------------

void Game::logic(float dt) 
{
    // Input behavior
    input(dt);

    // Update engine & client
    engine.update(dt);
    client.update();

    // Sync Camera with player entity position
    //looter::sync_camera_position(engine, client, looter::player_entity);

    // Render
    client.render(engine.get_render_items(), engine.get_registry());

    // add imgui here maybe
    
}

bool Game::quit(void)
{
    engine.shutdown();
    return true;
}

bool Game::handle_event(SDL_Event* event)
{
    return ImGui_ImplSDL3_ProcessEvent(event);
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
        engine.apply_movement(looter::player_entity, input.move_intent);
}