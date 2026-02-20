#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>


inline nlohmann::json load_json(const std::filesystem::path& path)
{
    std::ifstream file(path);
    if (!file)
        throw std::runtime_error("Failed to open: " + path.string());

    nlohmann::json data;
    file >> data;
    return data;
}