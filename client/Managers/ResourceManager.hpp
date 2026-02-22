#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <iostream> //debug

#include "../common/TextureID.hpp"
#include "../common/Animation.hpp"
#include "../common/types.hpp"

#include "../utils/json_functions.hpp"


struct SpriteDefinition
{
	std::unordered_map<State, TextureID> state_to_texture;
};


/* Sprite Manager */
class Sprites
{
private:
	std::unordered_map<SpriteDefinitionID, SpriteDefinition> m_definitions;
	std::unordered_map<TextureID, AnimationSet> m_animation_sets;

public:
	const SpriteDefinition* getSpriteDefinition(SpriteDefinitionID id);
	const AnimationSet* getAnimationSet(TextureID id);
	const TextureID* getTextureIDByState(SpriteDefinitionID id, State state);

	// [ ! ] Caution | Returns the actual underlying map
	std::unordered_map<TextureID, AnimationSet>& get_all_sets(void);

	bool addAnimationSet(TextureID id, AnimationSet& set);
};


/* Resource Manager */
class ResourceManager 
{
private:
	SDL_Renderer* m_renderer = nullptr;

	// Folder path
	const std::filesystem::path assets_folder_path { std::filesystem::current_path() / "assets" };

	// Textures
	TextureID m_nextID = 1;
	std::unordered_map<TextureID, SDL_Texture*> m_textures;//<- textures live here
	std::unordered_map<std::string, TextureID>  m_textureID_from_filename;

	// SpriteManager
	Sprites m_spriteManager;
	
	
	TextureID addTexture(const std::filesystem::path filename);

	bool load_textures();
	bool load_animations();

public:
	void register_renderer(SDL_Renderer* ren);
	void init(void);

	SDL_Texture* getTexture(const TextureID id);
	SDL_Texture* getTexture(const std::string filename);//filename _without_ extension

	AnimationSet* getAnimationSet(const TextureID id);
	std::unordered_map<TextureID, AnimationSet>& getAnimationSets(void);
};