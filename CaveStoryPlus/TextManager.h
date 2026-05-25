#pragma once
#include "structs.h"
#include <SDL2/SDL_ttf.h>
#include <string>

class Texture;
class TextManager
{
  public:
    TextManager();
    ~TextManager();

    TextManager(const TextManager &) = delete;
    TextManager &operator=(const TextManager &) = delete;

    TextManager(TextManager &&) = delete;
    TextManager &operator=(TextManager &&) = delete;

    Texture BakeText(const std::string &text, int ptSize, const Color4f &color = Color4f{1.f, 1.f, 1.f, 1.f}) const;

  private:
    TTF_Font *m_pUsedFont{};
};
