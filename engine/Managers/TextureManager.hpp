#pragma once

// TEMP
#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <unordered_map>
#include <map>
#include <string>
#include <filesystem>

using TextureID = uint32_t;


class TextureManager {
private:
	SDL_Renderer* m_renderer = nullptr;

	// Textures
	std::unordered_map<TextureID, SDL_Texture*> m_textures;
	bool addTexture(TextureID id, const std::string& filename);

public:
	TextureManager(SDL_Renderer* ren) : m_renderer(ren) {};
	void register_renderer(SDL_Renderer* ren);
	
	bool load_textures();

	SDL_Texture* getTexture(TextureID id);

};