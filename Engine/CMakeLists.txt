cmake_minimum_required(VERSION 3.15)
project(Engine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
  BaseGame.cpp
  BaseGame.h
  base.h
  Matrix2x3.cpp
  Matrix2x3.h
  SoundEffect.cpp
  SoundEffect.h
  SoundStream.cpp
  SoundStream.h
  structs.cpp
  structs.h
  SVGParser.cpp
  SVGParser.h
  Texture.cpp
  Texture.h
  Transform.h
  utils.cpp
  utils.h
  Vector2f.cpp
  Vector2f.h
)

target_include_directories(${PROJECT_NAME} PUBLIC .)

if (NOT WIN32)
  target_link_libraries(${PROJECT_NAME} PUBLIC
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
    SDL2_image::SDL2_image
    SDL2main
    GL
  )
endif()
