#include "TextureManager.hpp"

// ------------------
// ----- Public -----
// ------------------

/* Initialization */

void TextureManager::register_renderer(SDL_Renderer* ren) 
{
	this->m_renderer = ren;
}

void TextureManager::init(void) 
{
	if (!this->m_renderer)
	{
		std::cout << "Renderer not found!\n";
	}

	if (!this->load_textures())
	{
		std::cout << "Couldn't load textures\n";
	}

	this->load_animations(); // <- read json
}


/* Textures */

SDL_Texture* TextureManager::getTexture(const TextureID id)
{
	auto it = m_textures.find(id);
	return (it != m_textures.end()) ? it->second : nullptr;
}

SDL_Texture* TextureManager::getTexture(const std::string filename)
{
	auto it = m_textureID_by_filename.find(filename);
	if (it != m_textureID_by_filename.end())
	{
		const TextureID texture_id = it->second;
		return m_textures.at(texture_id);
	}
	return nullptr;
}


/* Animations */

AnimationSet* TextureManager::getAnimationSet(const TextureID id)
{
	auto it = m_animation_sets.find(id);
	return (it != m_animation_sets.end()) ? &it->second : nullptr;
}

std::unordered_map<TextureID, AnimationSet>& TextureManager::getAnimationSets(void)
{
	return m_animation_sets;
}


// -------------------
// ----- Private -----
// -------------------

/* Textures */

bool TextureManager::load_textures()
{
	std::vector<std::filesystem::path> pngs;

	for (const auto& entry : std::filesystem::directory_iterator(this->assets_folder_path / "textures")) 
	{
		if (entry.is_regular_file() && entry.path().extension() == ".png") 
		{
			pngs.push_back(entry.path());
		}
	}

	for (const std::filesystem::path& file : pngs) 
	{
		TextureID id = this->addTexture(file);
		if (id == 0)
		{
			continue;
		}
		// Store filename -> id mapping for later retrieval of animation clips
		this->m_textureID_by_filename[file.stem()] = id;
	}
	return true;
}

TextureID TextureManager::addTexture(const std::filesystem::path filename)
{
	if (!this->m_renderer)
		return 0;

	auto full_texture_path = this->assets_folder_path / "textures" / filename;
	auto* texture = IMG_LoadTexture(m_renderer, full_texture_path.string().c_str());

	if (!texture)
	{
		SDL_Log("IMG_LoadTexture error: %s", SDL_GetError());
		return 0;
	}

	// Set filtering to nearest
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

	m_textures.insert({ this->m_nextID, texture });
	this->m_nextID++;

	return this->m_nextID - 1;
}


/* Animations */

bool TextureManager::load_animations()
{
	for (const auto& [filename, id] : this->m_textureID_by_filename)
	{
		// Read json [ nlohmann ]
		auto filename_with_ext = filename + ".json";
		auto full_file_path = this->assets_folder_path / "animations" / filename_with_ext;
		if (!std::filesystem::exists(full_file_path))
			continue; //<- skip
		std::ifstream f(full_file_path);
		nlohmann::json data = nlohmann::json::parse(f);

		// Compile list of animation clips
		AnimationSet animation_set;
		for (auto& anim : data)
		{
			AnimationClip clip;
			clip.row = anim["row"];
			clip.frame_count= anim["frame_count"];
			clip.frame_time = anim["frame_time"];
			animation_set.animations.push_back(clip);
		}
		// Apply
		this->addAnimationSet(animation_set, id);
	}
	return true;
}

void TextureManager::addAnimationSet(const AnimationSet set, TextureID id) 
{
	m_animation_sets.insert_or_assign(id, set);
}