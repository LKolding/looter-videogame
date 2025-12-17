#include "TextureManager.hpp"


void TextureManager::register_renderer(SDL_Renderer* ren) 
{
	this->m_renderer = ren;
}


bool TextureManager::load_textures()
{
	std::vector<std::filesystem::path> files;

	for (const auto& entry : std::filesystem::directory_iterator(this->assets_folder_path / "textures")) 
	{
		if (entry.is_regular_file() && entry.path().extension() == ".png") 
		{
			files.push_back(entry.path().filename());
		}
	}

	for (const std::filesystem::path& file : files) 
	{
		if (!this->addTexture(file.string())) 
		{
			return false;
		}
	}

	return true;
}


bool TextureManager::addTexture(const std::string& filename)
{
	// Early exit if texture already exists with id
	if (this->getTexture(filename))
		return false;

	if (!this->m_renderer)
		return false;

	auto full_texture_path = this->assets_folder_path / "textures" / filename;
	auto* texture = IMG_LoadTexture(m_renderer, full_texture_path.string().c_str());

	if (!texture)
	{
		SDL_Log("IMG_LoadTexture error: %s", SDL_GetError());
		return false;
	}

	m_textures.insert({ filename, texture });

	return true;
}


SDL_Texture* TextureManager::getTexture(const std::string& filename)
{
	auto it = m_textures.find(filename);
	return (it != m_textures.end()) ? it->second : nullptr;
}

