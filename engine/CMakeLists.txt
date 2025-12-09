# CMakeList.txt : CMake project for engine


# Add source as library 
add_library (engine STATIC 
	"engine.cpp"
	"engine.hpp" 
 "Systems/MovementSystem.cpp" "Managers/TextureManager.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET engine PROPERTY CXX_STANDARD 20)
endif()

# idk what this does, and why it's here
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install targets
target_link_libraries(engine PUBLIC SDL3::SDL3 EnTT::EnTT)