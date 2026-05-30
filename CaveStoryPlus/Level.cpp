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
#include <iomanip>
#include <iostream>

const float Level::m_BgTextureScale{g_TileSize / 2.f};

Level::Level(const std::string &fullTexturePath, const std::string &collidersPath, const std::string &displayName,
             const Vector2f &spawnPos, MusicManager::Track track)
    : m_LevelName(displayName), m_CollidersPath(collidersPath), m_MusicTrack(track), m_SpawnPos(spawnPos)
{
    m_pFullTexture = new Texture(fullTexturePath);
    m_pNameTexture = new Texture(displayName, "Cave-Story.ttf", 48, Color4f{1.f, 1.f, 1.f, 1.f});
    m_pEnemiesTexture = new Texture("enemies.png");
    m_pInteractablesTexture = new Texture("interactables.png");

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
    delete m_pNameTexture;
    delete m_pEnemiesTexture;
    delete m_pInteractablesTexture;

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
    pEnemy->SetSpriteSheetTexture(*m_pEnemiesTexture);
    pEnemy->SetSoundManager(m_pSoundManager);
    m_Enemies.emplace_back(pEnemy);
}

void Level::SpawnInteractable(Interactable *pInteractable)
{
    assert(pInteractable && "Passing a nullptr as interactable");

    pInteractable->SetSpriteSheetTexture(m_pInteractablesTexture);

    // try to re-use free slot of previous deleted interactable
    for (int i{}; i < m_Interactables.size(); ++i)
    {
        if (!m_Interactables[i])
        {
            m_Interactables[i] = pInteractable;
            return;
        }
    }

    m_Interactables.emplace_back(pInteractable);
}

void Level::InteractWithInteractables(const Player &player, Game &game, bool holdingInteractKey)
{
    for (int i{}; i < m_Interactables.size(); ++i)
    {
        if (m_Interactables[i] && m_Interactables[i]->IsInside(player))
        {
            bool shouldDestroy{};
            if (holdingInteractKey)
            {
                shouldDestroy = m_Interactables[i]->OnInteract(game);
            }
            else
            {
                shouldDestroy = m_Interactables[i]->OnTouch(game);
            }

            if (shouldDestroy)
            {
                delete m_Interactables[i];
                m_Interactables[i] = nullptr;
            }
        }
    }
}

void Level::SetSpawnPos(const Vector2f &pos)
{
    m_SpawnPos = pos;
}

void Level::SetSoundManager(const SoundManager *pSoundManager)
{
    m_pSoundManager = pSoundManager;
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
        if (pEnemy && pEnemy->IsSolid())
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

    for (int i{}; i < m_Enemies.size(); ++i)
    {
        if (m_Enemies[i])
        {
            m_Enemies[i]->InteractWithPlayer(player);
            m_Enemies[i]->Update(delta);
            if (m_BulletManager.InteractWithEnemy(*m_Enemies[i]))
            {
                SpawnEnemyCollectibles(*m_Enemies[i], !player.HasMaximumHealth());
                delete m_Enemies[i];
                m_Enemies[i] = nullptr;
            }
        }
    }

    for (int i{}; i < m_Interactables.size(); ++i)
    {
        if (m_Interactables[i])
        {
            m_Interactables[i]->Update(delta);
            if (m_Interactables[i]->IsExpired())
            {
                delete m_Interactables[i];
                m_Interactables[i] = nullptr;
            }
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
        if (pEnemy)
        {
            pEnemy->Draw();
        }
    }

    for (const Interactable *pInteractable : m_Interactables)
    {
        if (pInteractable)
        {
            pInteractable->Draw();
        }
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

    for (const Enemy *pEnemy : m_Enemies)
    {
        if (pEnemy)
        {
            pEnemy->DrawGUI(viewport);
        }
    }
}

void Level::DrawDebug() const
{
    for (const Enemy *pEnemy : m_Enemies)
    {
        if (pEnemy)
        {
            pEnemy->DrawDebug();
        }
    }

    for (const Interactable *pInteractable : m_Interactables)
    {
        if (pInteractable)
        {
            pInteractable->DrawDebug();
        }
    }
}

std::ostream &operator<<(std::ostream &out, const Level &level)
{
    out << "=== Level: " << std::quoted(level.m_LevelName) << " ===\n";
    out << "Loaded " << level.m_Colliders.size() << " colliders from " << level.m_CollidersPath << '\n';
    out << "Enemy count: " << level.m_Enemies.size() << '\n';
    out << "Interactables count: " << level.m_Interactables.size() << '\n';
    out << "Spawn point: " << level.m_SpawnPos;
    return out;
}
