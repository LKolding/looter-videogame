# CMakeList.txt : CMake project for game

add_library(game STATIC game.hpp game.cpp)

# Game depends on engine
target_link_libraries(game PRIVATE engine)

# Include engine headers
target_include_directories(game PRIVATE ../engine)