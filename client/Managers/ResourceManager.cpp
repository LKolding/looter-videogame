#include "ResourceManager.hpp"

// ------------------
// ----- Public -----
// ------------------

/* Initialization */

void ResourceManager::register_renderer(SDL_Renderer* ren) 
{
	this->m_renderer = ren;
}

void ResourceManager::init(void) 
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

SDL_Texture* ResourceManager::getTexture(const TextureID id)
{
	auto it = m_textures.find(id);
	return (it != m_textures.end()) ? it->second : nullptr;
}

SDL_Texture* ResourceManager::getTexture(const std::string filename)
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

AnimationSet* ResourceManager::getAnimationSet(const TextureID id)
{
	auto it = m_animation_sets.find(id);
	return (it != m_animation_sets.end()) ? &it->second : nullptr;
}

std::unordered_map<TextureID, AnimationSet>& ResourceManager::getAnimationSets(void)
{
	return m_animation_sets;
}


// -------------------
// ----- Private -----
// -------------------

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
		this->m_textureID_by_filename[file.stem()] = id;
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
	for (const auto& [filename, id] : this->m_textureID_by_filename)
	{
		// Read json [ nlohmann ]
		auto filename_with_ext = filename + ".json";
		auto full_file_path = this->assets_folder_path / "animations" / filename_with_ext;
		if (!std::filesystem::exists(full_file_path))
			continue; //<- skip
		
		nlohmann::json data = load_json(full_file_path);

		auto& frames = data.at("frames");
		auto& meta = data.at("meta");


		// Read all frames into a vector of pairs
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


			
		// List of AnimationClip(s) containing Facing->Frames
		AnimationSet animation_set; // one per texture

		// Read meta data
		for (auto& animation_data : meta.at("frameTags"))
		{
			auto& temp = animation_data;

			AnimationClip _clip;
			_clip.frames = std::vector(
				all_frames.begin() + animation_data["from"].get<size_t>(),
				all_frames.begin() + animation_data["to"].get<size_t>() + 1
			);
			// Determine facing direction
			Direction direction;
			std::string facing = animation_data["name"].get<std::string>();
			if (facing == "south")
			{
				direction = Direction::South;
			}
			else if (facing == "north")
			{
				direction = Direction::North;
			}
			else if (facing == "west")
			{
				direction = Direction::West;
			}
			else if (facing == "east")
			{
				direction = Direction::East;
			}
			// Store animation
			animation_set._animations.try_emplace(direction, std::move(_clip));
		}
		// Apply
		this->addAnimationSet(id, animation_set);
	}
	return true;
}



void ResourceManager::addAnimationSet(TextureID id, AnimationSet set) 
{
	m_animation_sets[id] = std::move(set);
}