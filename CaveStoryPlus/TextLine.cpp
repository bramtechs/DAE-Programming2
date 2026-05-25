#include "TextLine.h"
#include "TextManager.h"

#include <string>

TextLine::TextLine(std::string text, const TextManager &textManager)
    : m_TextManager(textManager), m_Text(std::move(text)), m_Texture(BakeText())
{
}

Texture TextLine::BakeText() const
{
    const int clamped{std::min(m_CharsVisible, static_cast<int>(m_Text.size()))};
    const std::string slice{m_Text.substr(0, clamped)};
    return m_TextManager.BakeText(slice, 48);
}

void TextLine::Draw(const Vector2f &bottomLeft) const
{
    m_Texture.Draw(bottomLeft);
}

void TextLine::AdvanceText()
{
    ++m_CharsVisible;
    m_Texture = BakeText();
}

void TextLine::SkipText()
{
    m_CharsVisible = static_cast<int>(m_Text.size());
    m_Texture = BakeText();
}

bool TextLine::IsDone() const
{
    return m_CharsVisible >= static_cast<int>(m_Text.size());
}

float TextLine::GetTextHeight() const
{
    return m_Texture.GetHeight();
}
