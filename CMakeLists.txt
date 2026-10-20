cmake_minimum_required(VERSION 3.20)

project(PacManC LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(pacman
    src/main.c
)

target_include_directories(pacman PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
