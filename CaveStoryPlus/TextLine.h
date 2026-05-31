#pragma once
#include "Texture.h"

#include <string>

class TextManager;
class Texture;
class TextLine
{
  public:
    explicit TextLine(std::string text, const TextManager &textManager);

    void Draw(const Vector2f &bottomLeft) const;

    void AdvanceText();
    void SkipText();

    bool IsDone() const;
    float GetTextHeight() const;

  private:
    Texture BakeText() const;

    const TextManager &m_TextManager;
    const std::string m_Text{};
    size_t m_CharsVisible{};
    Texture m_Texture;
};
