#include "ResourceManager.hpp"


// -------------------------
// ----- SpriteManager -----
// -------------------------

/* Getters*/

const SpriteDefinition* Sprites::getSpriteDefinition(SpriteDefinitionID id)
{
	auto it = m_definitions.find(id);
	if (it != m_definitions.end())
	{
		return &m_definitions.at(id);
	}
	return nullptr;
};
const AnimationSet* Sprites::getAnimationSet(TextureID id)
{
	auto it = m_animation_sets.find(id);
	if (it != m_animation_sets.end())
	{
		return &m_animation_sets.at(id);
	}
	return nullptr;
};
const TextureID* Sprites::getTextureIDByState(SpriteDefinitionID id, State state)
{
	// locate definition
	auto it = m_definitions.find(id);
	if (it == m_definitions.end())
	{
		return nullptr; //<- fail
	}
	// locate texture
	auto it2= it->second.state_to_texture.find(state);
	if (it2 == it->second.state_to_texture.end())
	{
		return nullptr; //<- fail
	}
	return &it2->second; // return texture id
};

// [ ! ] Caution | Returns the actual underlying map
std::unordered_map<TextureID, AnimationSet>& Sprites::get_all_sets(void)
{
	return this->m_animation_sets;
}


/* Setters */

bool Sprites::addAnimationSet(TextureID id, AnimationSet& set)
{
	auto it = m_animation_sets.find(id);
	if (it == m_animation_sets.end())
	{
		m_animation_sets[id] = set;
		return true;
	}
	return false;
}


// ---------------------------
// ----- ResourceManager -----
// ---------------------------

// --- Public ---

/* Initialization */

void ResourceManager::register_renderer(SDL_Renderer* ren) 
{
	this->m_renderer = ren;
}

void ResourceManager::init(void) 
{
	if (!this->m_renderer)
	{
		throw std::runtime_error("Renderer not found!");
	}

	if (!this->load_textures())
	{
		throw std::runtime_error("Couldn't load textures!");
	}

	this->load_animations(); // <- read json
}

/* Textures */

SDL_Texture* ResourceManager::getTexture(const TextureID id)
{
	auto it = m_textures.find(id);
	return (it != m_textures.end()) ? it->second : nullptr;
}

SDL_Texture* ResourceManager::getTexture(const std::string filename)
{
	auto it = m_textureID_from_filename.find(filename);
	if (it != m_textureID_from_filename.end())
	{
		const TextureID texture_id = it->second;
		return m_textures.at(texture_id);
	}
	return nullptr;
}

/* Animations */

AnimationSet* ResourceManager::getAnimationSet(const TextureID id)
{
	return const_cast<AnimationSet*>(m_spriteManager.getAnimationSet(id));
}

// [ ! ] Caution | Returns the actual underlying map
std::unordered_map<TextureID, AnimationSet>& ResourceManager::getAnimationSets(void)
{
	return m_spriteManager.get_all_sets();
}

// --- Private ---

/* Textures */

bool ResourceManager::load_textures()
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
		this->m_textureID_from_filename[file.stem()] = id;
	}
	return true;
}

TextureID ResourceManager::addTexture(const std::filesystem::path filename)
{
	if (!this->m_renderer)
		return 0;

	const auto full_texture_path = this->assets_folder_path / "textures" / filename;
	auto* texture = IMG_LoadTexture(m_renderer, full_texture_path.string().c_str());

	if (!texture)
	{
		SDL_Log("IMG_LoadTexture error: %s", SDL_GetError());
		return 0;
	}

	// Set filtering to nearest
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

	// Store texture
	m_textures.insert({ this->m_nextID, texture });

	this->m_nextID++;
	return this->m_nextID - 1; // return ID of _current_ texture
}

/* Animations */

bool ResourceManager::load_animations()
{
	for (const auto& [filename, id] : this->m_textureID_from_filename)
	{
		// Read json [ nlohmann ]
		auto filename_with_ext = filename + ".json";
		auto full_file_path = this->assets_folder_path / "animations" / filename_with_ext;
		if (!std::filesystem::exists(full_file_path))
			continue; //<- skip
		
		nlohmann::json json_data = load_json(full_file_path);

		auto& frames = json_data.at("frames");
		auto& meta = json_data.at("meta");


		// Read _all_ frames into a vector of pairs
		std::vector<std::pair<std::string, AnimationFrame>> all_frames_with_keys;
		for (auto& [key, frame] : frames.items())
		{
			AnimationFrame _frame{
				.x = frame["frame"]["x"].get<int>(),
				.y = frame["frame"]["y"].get<int>(),
				.w = frame["frame"]["w"].get<int>(),
				.h = frame["frame"]["h"].get<int>(),
				.duration = frame["duration"].get<int>()
			};
			all_frames_with_keys.emplace_back(key, _frame);
		}
		// Sort frames by the numeric index in the key, e.g., "player_idle 0.aseprite"
		std::sort(all_frames_with_keys.begin(), all_frames_with_keys.end(),
			[](const auto& a, const auto& b) {
				auto extract_index = [](const std::string& s) {
					size_t pos1 = s.find_last_of(' ');
					size_t pos2 = s.find(".aseprite");
					return std::stoi(s.substr(pos1 + 1, pos2 - pos1 - 1));
				};
				return extract_index(a.first) < extract_index(b.first);
			});
		// Now extract just the frames
		std::vector<AnimationFrame> all_frames;
		for (auto& [key, frame] : all_frames_with_keys)
			all_frames.push_back(frame);


		AnimationSet animation_set; // one per texture

		// Read meta data
		for (auto& animation_json : meta.at("frameTags"))
		{
			auto& temp = animation_json;

			AnimationClip _clip;
			_clip.frames = std::vector(
				all_frames.begin() + animation_json["from"].get<size_t>(),
				all_frames.begin() + animation_json["to"].get<size_t>() + 1
			);
			// Determine facing direction
			Direction direction;
			std::string facing = animation_json["name"].get<std::string>();
			if (facing == "south")
				direction = Direction::South;
			else if (facing == "north")
				direction = Direction::North;
			else if (facing == "west")
				direction = Direction::West;
			else if (facing == "east")
				direction = Direction::East;

			// Store animation
			animation_set.clips.try_emplace(direction, std::move(_clip));
		}
		// Store animation set
		if (!m_spriteManager.addAnimationSet(id, animation_set))
		{
			throw std::runtime_error("Couldn't store animation set!");
		}
	}
	return true;
}