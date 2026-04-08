cmake_minimum_required(VERSION 3.15)
project(Engine)
set(CMAKE_CXX_STANDARD 14)
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
