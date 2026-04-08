#include "Level.h"
#include "ColliderReader.h"
#include "Editor.h"
#include "Enemy.h"
#include "Game.h"
#include "Texture.h"
#include "pch.h"
#include "utils.h"

#include <cassert>
#include <iostream>

Level::Level(const std::string &fullTexturePath, const std::string &collidersPath) : m_CollidersPath(collidersPath)
{
    m_pFullTexture = new Texture(fullTexturePath);

    m_LevelCols = static_cast<int>(m_pFullTexture->GetWidth()) / 16;
    m_LevelRows = static_cast<int>(m_pFullTexture->GetHeight()) / 16;

    ColliderReader reader(m_CollidersPath);
    const size_t amount = reader.ReadAllInto(m_Colliders);
    if (amount > 0)
    {
        std::cout << "Read " << amount << " colliders from " << m_CollidersPath << std::endl;
    }
}

Level::~Level()
{
    delete m_pFullTexture;

    for (int i{}; i < m_Enemies.size(); ++i)
    {
        delete m_Enemies[i];
    }
}

void Level::SpawnEnemy(Enemy *pEnemy)
{
    assert(pEnemy && "Passing a nullptr as enemy");
    m_Enemies.emplace_back(pEnemy);
}

void Level::Update(float delta, Player &player)
{
    for (int i{}; i < m_Enemies.size(); ++i)
    {
        m_Enemies[i]->InteractWithPlayer(player);
        m_Enemies[i]->Update(delta);
    }
}

void Level::Draw() const
{
    const float scaledWidth{m_pFullTexture->GetWidth() / g_TileSize * 2.f};
    const float scaledHeight{m_pFullTexture->GetHeight() / g_TileSize * 2.f};
    m_pFullTexture->Draw(Rectf{0.f, 0.f, scaledWidth, scaledHeight});

    for (int i{}; i < m_Enemies.size(); ++i)
    {
        m_Enemies[i]->Draw();
        m_Enemies[i]->DrawDebug();
    }
}
