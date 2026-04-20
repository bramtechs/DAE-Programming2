#include "MultiLineLabel.h"
#include "Texture.h"

#include <iomanip>
#include <iostream>
#include <sstream>

MultiLineLabel::MultiLineLabel(const std::string &fontPath, int ptSize)
{
    m_pFont = TTF_OpenFont(fontPath.c_str(), ptSize);
    if (m_pFont == nullptr)
    {
        std::cerr << "Failed to load font " << std::quoted(fontPath) << " for MultiLineLabel: " << TTF_GetError()
                  << std::endl;
        return;
    }
}

MultiLineLabel::~MultiLineLabel()
{
    for (int i{}; i < m_Textures.size(); ++i)
    {
        delete m_Textures[i];
    }
}

void MultiLineLabel::RegisterLine(const std::string &text, const Color4f &color)
{
    m_Textures.push_back(new Texture(text, m_pFont, color));
}

void MultiLineLabel::RegisterLines(const std::string &lines, const Color4f &color)
{
    std::stringstream ss{lines};
    std::string line{};
    while (std::getline(ss, line))
    {

        RegisterLine(line, color);
    }
}

std::string MultiLineLabel::TrimString(std::string line)
{
    const char *pWhiteSpace{"\t\n\r "};
    line.erase(0, line.find_first_not_of(pWhiteSpace));
    line.erase(line.find_last_not_of(pWhiteSpace) + 1);
    return line;
}

void MultiLineLabel::Draw(const Vector2f &pos) const
{
    float yOffset{};
    for (int i{}; i < m_Textures.size(); ++i)
    {
        const Vector2f itemPos(pos.x, pos.y + yOffset);
        m_Textures[i]->Draw(itemPos);
        yOffset += m_Textures[i]->GetHeight();
    }
}
