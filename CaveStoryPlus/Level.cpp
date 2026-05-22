#include "pch.h"
#include "Level.h"
#include "ColliderReader.h"
#include "Editor.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "HeartInteractable.h"
#include "GoldInteractable.h"
#include "Interactable.h"
#include "Texture.h"

#include <cassert>
#include <iostream>

Level::Level(const std::string &fullTexturePath, const std::string &collidersPath, const std::string &displayName,
             const Vector2f &spawnPos)
    : m_CollidersPath(collidersPath), m_SpawnPos(spawnPos)
{
    m_pFullTexture = new Texture(fullTexturePath);
    m_pNameTexture = new Texture(displayName, "Cave-Story.ttf", 48, Color4f{1.f, 1.f, 1.f, 1.f});

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

    if (m_pNameTexture)
    {
        delete m_pNameTexture;
    }

    for (Enemy *pEnemy : m_Enemies)
    {
        delete pEnemy;
    }

    for (Interactable *pInteractable : m_Interactables)
    {
        delete pInteractable;
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

void Level::SetSpawnPos(const Vector2f &pos)
{
    m_SpawnPos = pos;
}

Rectf Level::GetBounds() const
{
    const float levelWidth{m_pFullTexture ? (m_pFullTexture->GetWidth() / m_BgTextureScale) : 0.f};
    const float levelHeight{m_pFullTexture ? (m_pFullTexture->GetHeight() / m_BgTextureScale) : 0.f};

    return Rectf{0.f, 0.f, levelWidth, levelHeight};
}

const std::vector<PolygonCollider> Level::GetSolidEnemyColliders() const
{
    static std::vector<PolygonCollider> s_Colliders{};

    s_Colliders.clear();
    for (const Enemy *pEnemy : m_Enemies)
    {
        if (pEnemy->IsSolid())
        {
            s_Colliders.emplace_back(pEnemy->GetRegion());
        }
    }

    return s_Colliders;
}

void Level::Update(float delta, Player &player)
{
    m_BulletManager.Update(delta);
    m_BulletManager.InteractWithLevel(*this);

    for (auto it{m_Enemies.begin()}; it != m_Enemies.end();)
    {
        Enemy *pEnemy = *it;
        pEnemy->InteractWithPlayer(player);
        pEnemy->Update(delta);
        if (m_BulletManager.InteractWithEnemy(*pEnemy))
        {
            SpawnEnemyCollectibles(*pEnemy, !player.HasMaximumHealth());
            delete *it;
            it = m_Enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto it{m_Interactables.begin()}; it != m_Interactables.end();)
    {
        (*it)->Update(delta);
        if ((*it)->IsExpired())
        {
            delete *it;
            it = m_Interactables.erase(it);
        }
        else
        {
            ++it;
        }
    }

    if (m_NameShownTimer > 0.f)
    {
        m_NameShownTimer -= delta;
    }
    else
    {
        // texture is no longer needed after being shown
        delete m_pNameTexture;
        m_pNameTexture = nullptr;
    }
}

void Level::SpawnEnemyCollectibles(const Enemy &enemy, bool playerIsDamaged)
{
    if (playerIsDamaged && rand() % 100 < 50)
    {
        SpawnInteractable(new HeartInteractable(enemy.GetCenter()));
        return;
    }

    // when killed the enemy
    for (int i{}; i < enemy.GetGoldDropCount(); ++i)
    {
        SpawnInteractable(new GoldInteractable(enemy.GetCenter(), *this));
    }
}

void Level::Draw() const
{
    const float scaledWidth{m_pFullTexture->GetWidth() / m_BgTextureScale};
    const float scaledHeight{m_pFullTexture->GetHeight() / m_BgTextureScale};
    m_pFullTexture->Draw(Rectf{0.f, 0.f, scaledWidth, scaledHeight});

    for (const Enemy *pEnemy : m_Enemies)
    {
        pEnemy->Draw();
    }

    for (const Interactable *pInteractable : m_Interactables)
    {
        pInteractable->Draw();
    }

    m_BulletManager.Draw();
}

void Level::DrawGUI(const Rectf &viewport) const
{
    if (m_pNameTexture && m_NameShownTimer > 0.f)
    {
        Vector2f pos{viewport.width * 0.5f, viewport.height * 0.7f};
        pos.x -= m_pNameTexture->GetWidth() * 0.5f;
        pos.y -= m_pNameTexture->GetHeight() * 0.5f;
        m_pNameTexture->Draw(pos);
    }
}

void Level::DrawDebug() const
{
    for (const Enemy *pEnemy : m_Enemies)
    {
        pEnemy->DrawDebug();
    }

    for (const Interactable *pInteractable : m_Interactables)
    {
        pInteractable->DrawDebug();
    }
}
