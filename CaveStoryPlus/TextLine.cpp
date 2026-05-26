#include "pch.h"
#include "utils.h"
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
    const int clamped{utils::Clamp(static_cast<int>(m_CharsVisible), 1, static_cast<int>(m_Text.size()))};
    const std::string slice{m_Text.substr(0, static_cast<size_t>(clamped))};
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
