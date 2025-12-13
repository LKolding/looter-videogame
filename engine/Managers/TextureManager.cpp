#include "TextureManager.hpp"

void TextureManager::register_renderer(SDL_Renderer* ren) 
{
	this->m_renderer = ren;
}

bool TextureManager::load_textures() 
{
	std::map<TextureID, std::filesystem::path> texture_filename;

	// Player texture definition
	texture_filename.insert({ 1, std::filesystem::path("assets") / "textures" / "link_spritesheet.png"});

	// Check if file exists
	if (!std::filesystem::exists(std::filesystem::path("assets") / "textures" / "link_spritesheet.png"))
	{
		std::cout << "File doesn't exist\n";
		return false;
	}

	// Add all textures
	for (const auto& [id, path] : texture_filename) {
		if (!this->addTexture(id, path.string()))
			return false;  // fail if texture didn't load
	}
	
	return true;
}

SDL_Texture* TextureManager::getTexture(TextureID id) 
{
	auto it = m_textures.find(id);
	return (it != m_textures.end()) ? it->second : nullptr;
}

bool TextureManager::addTexture(TextureID id, const std::string& filename) {
	// Early exit if texture already exists with id
	if (this->getTexture(id))
		return false;

	if (!this->m_renderer)
		return false;

	auto* texture = IMG_LoadTexture(m_renderer, filename.c_str());

	if (!texture)
	{
		SDL_Log("IMG_LoadTexture error: %s", SDL_GetError());
		return false;
	}

	m_textures.insert({ id, texture });

	return true;
}