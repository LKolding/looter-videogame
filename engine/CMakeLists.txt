# CMakeList.txt : CMake project for engine


# Add source as library 
add_library (engine STATIC 
	  "engine.cpp"

    "Systems/Physics/VelocitySystem.cpp"
    "Systems/Physics/PositionSystem.cpp"

    "Systems/StateSystem.cpp"
    "Systems/StateAnimationSystem.cpp"
    "Systems/TextureAnimationSystem.cpp"

    "Factory/EntityFactory.cpp"
  )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET engine PROPERTY CXX_STANDARD 20)
endif()

# Find packages from vcpkg
find_package(EnTT CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# idk what this does, and why it's here
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install targets
target_link_libraries(engine PUBLIC EnTT::EnTT nlohmann_json::nlohmann_json)