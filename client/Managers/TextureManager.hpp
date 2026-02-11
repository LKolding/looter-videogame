#pragma once

// TEMP
#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <nlohmann/json.hpp>

#include <unordered_map>
#include <map>
#include <string>
#include <filesystem>

class TextureManager {
private:
	SDL_Renderer* m_renderer = nullptr;

	// Folder path
	const std::filesystem::path assets_folder_path = std::filesystem::path("assets");

	// Textures
	std::unordered_map<std::string, SDL_Texture*> m_textures;
	bool addTexture(const std::string& filename);

public:
	TextureManager(SDL_Renderer* ren) : m_renderer(ren) {};
	void register_renderer(SDL_Renderer* ren);
	
	bool load_textures();

	SDL_Texture* getTexture(const std::string& filename);

};