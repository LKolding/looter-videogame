# CMakeList.txt : CMake project for game

add_library(client STATIC 
    "client.cpp"

    "main.cpp"

    "Managers/TextureManager.cpp"
    "Managers/InputManager.cpp"
)

# Find packages from vcpkg
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)

# Game depends on engine and SDL
target_link_libraries(client PRIVATE engine SDL3::SDL3 $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)

# Include engine headers
target_include_directories(client PRIVATE ../engine)
