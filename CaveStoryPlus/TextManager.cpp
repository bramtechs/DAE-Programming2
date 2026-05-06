#include "pch.h"
#include "TextManager.h"
#include "Texture.h"

#include <SDL2/SDL_ttf.h>
#include <iostream>

TextManager::TextManager()
{
    m_pUsedFont = TTF_OpenFont("Cave-Story.ttf", 22);
    if (m_pUsedFont == nullptr)
    {
        std::cerr << "Failed to open font: " << TTF_GetError() << std::endl;
    }
}

TextManager::~TextManager()
{
    if (m_pUsedFont)
    {
        TTF_CloseFont(m_pUsedFont);
    }
}

Texture *TextManager::BakeText(const std::string &text, int ptSize, const Color4f &color)
{
    if (!m_pUsedFont)
    {
        return new Texture("");
    }

    if (TTF_SetFontSize(m_pUsedFont, ptSize) != 0)
    {
        std::cerr << "Failed to adjust font size: " << TTF_GetError() << std::endl;
    }

    return new Texture(text, m_pUsedFont, color);
}
