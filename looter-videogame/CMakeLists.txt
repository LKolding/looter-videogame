# CMakeList.txt : CMake project for looter-videogame, include source and define
# project specific logic here.
#

# Enable FetchContent
include(FetchContent)


# --- EnTT ---
FetchContent_Declare(
	EnTT
	GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG 3.16.0
)
FetchContent_MakeAvailable(EnTT)

# --- SDL3 ---
FetchContent_Declare(
	SDL3
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG origin/main
)
FetchContent_MakeAvailable(SDL3)

# Add source to this project's executable.
add_executable (looter-videogame "looter-videogame.cpp" "looter-videogame.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET looter-videogame PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(game PRIVATE SDL3::SDL3 EnTT::EnTT)