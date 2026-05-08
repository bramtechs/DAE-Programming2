#include "Level.h"
#include "ColliderReader.h"
#include "Editor.h"
#include "Enemy.h"
#include "Game.h"
#include "GoldInteractable.h"
#include "Interactable.h"
#include "Texture.h"
#include "pch.h"
#include "utils.h"

#include <cassert>
#include <iostream>

Level::Level(const std::string &fullTexturePath, const std::string &collidersPath, const Vector2f &spawnPos)
    : m_CollidersPath(collidersPath), m_SpawnPos(spawnPos)
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

    for (int i{}; i < m_Interactables.size(); ++i)
    {
        delete m_Interactables[i];
    }
}

void Level::SpawnEnemy(Enemy *pEnemy)
{
    assert(pEnemy && "Passing a nullptr as enemy");
    m_Enemies.emplace_back(pEnemy);
}

void Level::SpawnInteractable(Interactable *pInteractable)
{
    assert(pInteractable && "Passing a nullptr as interactable");
    m_Interactables.emplace_back(pInteractable);
}

void Level::InteractWithInteractables(const Player &player, Game &game, bool holdingInteractKey)
{
    auto it{m_Interactables.begin()};
    while (it != m_Interactables.end())
    {
        if ((*it)->IsInside(player))
        {
            bool shouldDestroy{};
            if (holdingInteractKey)
            {
                shouldDestroy = (*it)->OnInteract(game);
            }
            else
            {
                shouldDestroy = (*it)->OnTouch(game);
            }

            if (shouldDestroy)
            {
                delete *it;
                it = m_Interactables.erase(it);
                continue;
            }
        }

        ++it;
    }
}

void Level::Update(float delta, Player &player)
{
    m_BulletManager.Update(delta);

    for (auto it{m_Enemies.begin()}; it != m_Enemies.end();)
    {
        Enemy *pEnemy = *it;
        pEnemy->InteractWithPlayer(player);
        pEnemy->Update(delta);
        if (m_BulletManager.InteractWithEnemy(*pEnemy))
        {
            SpawnInteractable(new GoldInteractable(pEnemy->GetPosition(), *this));

            // when killed the enemy
            delete *it;
            it = m_Enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (Interactable *pInteractable : m_Interactables)
    {
        pInteractable->Update(delta);
    }
}

void Level::Draw() const
{
    const float scaledWidth{m_pFullTexture->GetWidth() / g_TileSize * 2.f};
    const float scaledHeight{m_pFullTexture->GetHeight() / g_TileSize * 2.f};
    m_pFullTexture->Draw(Rectf{0.f, 0.f, scaledWidth, scaledHeight});

    for (const Enemy *pEnemy : m_Enemies)
    {
        pEnemy->Draw();
        pEnemy->DrawDebug();
    }

    m_BulletManager.Draw();

    for (const Interactable *pInteractable : m_Interactables)
    {
        pInteractable->Draw();
        pInteractable->DrawDebug();
    }
}
