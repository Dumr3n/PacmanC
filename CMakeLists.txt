cmake_minimum_required(VERSION 3.20)

project(PacManC LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.2
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(raylib)

add_library(pacmanCore STATIC
    src/maze.c
    src/player.c
    src/game.c
)

target_include_directories(pacmanCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(pacman
    src/main.c
    src/renderer.c
)

target_link_libraries(pacman PRIVATE 
    pacmanCore
    raylib
)

enable_testing()

add_executable(test_maze
    tests/test_maze.c
)

add_executable(test_player
    tests/test_player.c
)

add_executable(test_game
    tests/test_game.c
)

target_link_libraries(test_maze PRIVATE pacmanCore)
target_link_libraries(test_player PRIVATE pacmanCore)
target_link_libraries(test_game PRIVATE pacmanCore)