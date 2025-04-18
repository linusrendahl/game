cmake_minimum_required(VERSION 3.10)
project(Game)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# This assumes the SDL_image source is available in vendored/SDL_image
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

add_executable(Game main.c controllers/player.c controllers/enemy.c controllers/sdl.c controllers/map.c controllers/game.c controllers/ui.c)

# Link to the actual SDL3 library.
target_link_libraries(Game PRIVATE SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf SDL3::SDL3)
