#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <nlohmann/json.hpp>

#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <iostream> //debug

#include "../common/TextureID.hpp"
#include "../common/AnimationClip.hpp"


class TextureManager 
{
private:
	SDL_Renderer* m_renderer = nullptr;

	// Folder path
	const std::filesystem::path assets_folder_path { std::filesystem::current_path() / "assets" };

	// Textures
	TextureID m_nextID = 1;
	std::unordered_map<std::string, TextureID> m_textureID_by_filename;
	std::unordered_map<TextureID, SDL_Texture*> m_textures;
	std::unordered_map<TextureID, AnimationSet> m_animation_sets;

	TextureID addTexture(const std::filesystem::path filename);
	void addAnimationSet(const AnimationSet set, TextureID id);

	bool load_textures();
	bool load_animations();

public:
	TextureManager() = default;

	void register_renderer(SDL_Renderer* ren);
	void init(void);

	SDL_Texture* getTexture(const TextureID id);
	AnimationSet* getAnimationSet(const TextureID id);
	std::unordered_map<TextureID, AnimationSet>& getAnimationSets(void);

};