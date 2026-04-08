#pragma once
#include "structs.h"
#include <SDL_ttf.h>
#include <string>

class Texture;
class TextManager
{
  public:
    TextManager();
    ~TextManager();

    Texture *BakeText(const std::string &text, int ptSize, const Color4f &color = Color4f{1.f, 1.f, 1.f, 1.f});

  private:
    TTF_Font *m_pUsedFont{};
};
