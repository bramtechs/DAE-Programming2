#pragma once
#include "SDL_ttf.h"
#include "pch.h"
#include <vector>

class Texture;
class MultiLineLabel
{
  public:
    explicit MultiLineLabel(const std::string &fontPath, int ptSize);
    ~MultiLineLabel();

    MultiLineLabel(const MultiLineLabel &o) = delete;
    MultiLineLabel &operator=(const MultiLineLabel &o) = delete;

    void RegisterLine(const std::string &text, const Color4f &color = Color4f{1.f, 1.f, 1.f, 1.f});
    void RegisterLines(const std::string &lines, const Color4f &color = Color4f{1.f, 1.f, 1.f, 1.f});

    void Draw(const Vector2f &pos) const;

  private:
    static std::string TrimString(std::string line);

    std::vector<Texture *> m_Textures{};
    TTF_Font *m_pFont{};
};
