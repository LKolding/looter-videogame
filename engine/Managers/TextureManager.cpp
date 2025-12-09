#include "TextureManager.hpp"


TextureManager::TextureManager(SDL_Renderer* renderer) 
{
	this->m_renderer = renderer;
}


SDL_Texture* TextureManager::getTexture(TextureID id) 
{
	auto it = m_textures.find(id);
	return (it != m_textures.end()) ? &it->second : nullptr;
}