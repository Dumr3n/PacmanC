cmake_minimum_required(VERSION 3.20)

project(PacManC LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

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
)

target_link_libraries(pacman PRIVATE pacmanCore)

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