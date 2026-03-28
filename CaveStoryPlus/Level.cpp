#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "Game.h"
#include "utils.h"
#include "Editor.h"

#include <iostream>

Level::Level(const std::string& fullTexturePath, const std::string& levelPath)
{
    m_pFullTexture = new Texture(fullTexturePath);

    m_LevelCols = static_cast<int>(m_pFullTexture->GetWidth()) / 16;
    m_LevelRows = static_cast<int>(m_pFullTexture->GetHeight()) / 16;
}

Level::~Level()
{
    delete m_pFullTexture;
}

void Level::Update(float delta)
{
    
}

void Level::Draw() const
{
    const float scaledWidth{ m_pFullTexture->GetWidth() / g_TileSize * 2.f };
    const float scaledHeight{ m_pFullTexture->GetHeight() / g_TileSize * 2.f };
    m_pFullTexture->Draw(Rectf{ 0.f, 0.f, scaledWidth, scaledHeight });
}
