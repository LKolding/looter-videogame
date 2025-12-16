# CMakeList.txt : CMake project for engine


# Add source as library 
add_library (engine STATIC 
	"engine.cpp"
	"engine.hpp"

    "Systems/VelocitySystem.cpp"
    "Systems/TextureAnimationSystem.cpp"

    "Managers/TextureManager.cpp"
    "Managers/InputManager.cpp"

    "Factory/EntityFactory.cpp"
  )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET engine PROPERTY CXX_STANDARD 20)
endif()

# Find packages from vcpkg
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Copy assets directory to the build directory
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
)
# Make sure the executable depends on it
add_dependencies(engine copy_assets)

# idk what this does, and why it's here
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install targets
target_link_libraries(engine PUBLIC SDL3::SDL3 $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static> EnTT::EnTT nlohmann_json::nlohmann_json)