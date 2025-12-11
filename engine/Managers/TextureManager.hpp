#pragma once

#include <SDL3/SDL.h>
#include <unordered_map>

using TextureID = uint32_t;


class TextureManager {
public:
	TextureManager(SDL_Renderer* renderer): m_renderer(renderer) {};
	
	SDL_Texture* getTexture(TextureID id);

private:
	SDL_Renderer* m_renderer = nullptr;

	// Textures
	std::unordered_map<TextureID, SDL_Texture*> m_textures;
};