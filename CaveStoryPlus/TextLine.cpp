#include "pch.h"
#include "TextLine.h"
#include "TextManager.h"

#include <algorithm>
#include <cassert>
#include <string>

TextLine::TextLine(std::string text, const TextManager *pTextManager)
    : m_pTextManager(pTextManager), m_Text(std::move(text)), m_Texture(BakeText())
{
}

Texture TextLine::BakeText() const
{
    const size_t clamped{std::clamp(m_CharsVisible, size_t{1}, m_Text.size())};
    const std::string slice{m_Text.substr(0, clamped)};
    assert(m_pTextManager && "TextManager is null");
    return m_pTextManager->BakeText(slice, 48);
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
    m_CharsVisible = m_Text.size();
    m_Texture = BakeText();
}

bool TextLine::IsDone() const
{
    return m_CharsVisible >= m_Text.size();
}

float TextLine::GetTextHeight() const
{
    return m_Texture.GetHeight();
}
