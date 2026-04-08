cmake_minimum_required(VERSION 3.15)
project(CaveStoryPlusRoot CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(Libraries/SDLImage/SDL2_image-2.8.4/include)
include_directories(Libraries/SDLMain/SDL2-2.30.11/include)
include_directories(Libraries/SDLMixer/SDL2_mixer-2.8.0/include)
include_directories(Libraries/SDLTtf/SDL2_ttf-2.24.0/include)

link_directories(Libraries/SDLImage/SDL2_image-2.8.4/lib/x64)
link_directories(Libraries/SDLMain/SDL2-2.30.11/lib/x64)
link_directories(Libraries/SDLMixer/SDL2_mixer-2.8.0/lib/x64)
link_directories(Libraries/SDLTtf/SDL2_ttf-2.24.0/lib/x64)

add_subdirectory(CaveStoryPlus)
add_subdirectory(Engine)
