# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Project config starts here
project ("looter-videogame")

# Enable FetchContent
#include(FetchContent)



# Enable vcpkg
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

# Find packages from vcpkg
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)



# --- EnTT ---
#FetchContent_Declare(
#	EnTT
#	GIT_REPOSITORY https://github.com/skypjack/entt.git
#    GIT_TAG main
#)
#FetchContent_MakeAvailable(EnTT)

# --- SDL3 ---
#set(BUILD_SHARED_LIBS OFF)
#set(SDL_STATIC ON)

#FetchContent_Declare(
#	SDL3
#	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
#    GIT_TAG origin/main
#)
#FetchContent_MakeAvailable(SDL3)


# Include sub-projects.
add_subdirectory ("engine")
add_subdirectory ("game")

# Make executable
add_executable(videogame_launcher "launcher/launcher.cpp")
target_link_libraries(videogame_launcher PRIVATE engine game)