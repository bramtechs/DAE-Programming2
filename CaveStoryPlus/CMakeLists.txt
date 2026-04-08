cmake_minimum_required(VERSION 3.15)
project(CaveStoryPlus CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
  BatEnemy.cpp
  BatEnemy.h
  Camera.cpp
  Camera.h
  ColliderReader.cpp
  ColliderReader.h
  ColliderWriter.cpp
  ColliderWriter.h
  Editor.cpp
  Editor.h
  Enemy.cpp
  Enemy.h
  Game.cpp
  Game.h
  Interactable.h
  Interactable.cpp
  LifeCapsule.h
  LifeCapsule.cpp
  LevelBuilder.cpp
  LevelBuilder.h
  Level.cpp
  Level.h
  main.cpp
  pch.cpp
  pch.h
  Player.cpp
  Player.h
  PolygonCollider.cpp
  PolygonCollider.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Engine)

set(SDL_DLLS
  ${CMAKE_SOURCE_DIR}/Libraries/SDLMain/SDL2-2.30.11/lib/x64/SDL2.dll
  ${CMAKE_SOURCE_DIR}/Libraries/SDLImage/SDL2_image-2.8.4/lib/x64/SDL2_image.dll
  ${CMAKE_SOURCE_DIR}/Libraries/SDLMixer/SDL2_mixer-2.8.0/lib/x64/SDL2_mixer.dll
  ${CMAKE_SOURCE_DIR}/Libraries/SDLTtf/SDL2_ttf-2.24.0/lib/x64/SDL2_ttf.dll
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${SDL_DLLS}
  $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

file(GLOB RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Resources/*)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${RESOURCE_FILES}
  $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
