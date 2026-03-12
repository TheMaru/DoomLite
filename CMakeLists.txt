cmake_minimum_required(VERSION 3.20)
project(DoomLite VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
  src/main.cpp
  src/platform/sdl2/platform_sdl2.cpp
)

add_executable(DoomLite ${SOURCES})
target_include_directories(DoomLite PRIVATE src/ /opt/homebrew/include)
target_link_directories(DoomLite PRIVATE /opt/homebrew/lib)
target_link_libraries(DoomLite PRIVATE SDL2)
