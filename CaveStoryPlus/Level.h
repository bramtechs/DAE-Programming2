#pragma once
#include "BulletManager.h"
#include "PolygonCollider.h"
#include "Game.h"
#include "structs.h"

#include <ostream>
#include <cassert>
#include <string>
#include <vector>

class Interactable;
class SoundManager;
class Game;
class Editor;
class Camera;
class Texture;
class Enemy;
class Player;

class Level final
{
  public:
    explicit Level(const std::string &fullTexturePath, const std::string &collidersPath, const std::string &displayName,
                   const Vector2f &spawnPos, MusicManager::Track track);
    ~Level();
    Level(const Level &) = delete;
    Level(Level &&) = delete;
    Level &operator=(Level &&) = delete;
    Level &operator=(const Level &) = delete;

    void Update(float delta, Player &player);
    void Draw() const;
    void DrawGUI(const Rectf &viewport) const;
    void DrawDebug() const;

    void GetLevelSize(int &outWidth, int &outHeight) const;

    void AddColliderAround(const Vector2f &center, float radius);

    void DeleteCollider(int index);

    void SpawnEnemy(Enemy *pEnemy);
    void SpawnInteractable(Interactable *pInteractable);

    void InteractWithInteractables(const Player &player, Game &game, bool holdingInteractKey);

    void SetSpawnPos(const Vector2f &pos);

    void SetSoundManager(const SoundManager *pSoundManager);

    Rectf GetBounds() const;

    std::vector<PolygonCollider> GetSolidEnemyColliders() const;

    const std::vector<PolygonCollider> &GetColliders() const
    {
        return m_Colliders;
    }

    std::vector<PolygonCollider> &GetColliders()
    {
        return m_Colliders;
    }

    MusicManager::Track GetMusicTrack() const
    {
        return m_MusicTrack;
    }

    const std::string &GetCollidersFilePath() const
    {
        return m_CollidersPath;
    }

    const Vector2f &GetSpawnPos() const
    {
        return m_SpawnPos;
    }

    BulletManager &GetBulletManager()
    {
        return m_BulletManager;
    }

    const SoundManager &GetSoundManager() const
    {
        assert(m_pSoundManager);
        return *m_pSoundManager;
    }

    friend std::ostream &operator<<(std::ostream &out, const Level &level);

  private:
    static const float m_BgTextureScale;

    void SpawnEnemyCollectibles(const Enemy &enemy, bool playerIsDamaged);

    void DrawTileGrid() const;
    void DrawColliders() const;

    const std::string m_LevelName;
    const std::string m_CollidersPath;
    const MusicManager::Track m_MusicTrack;

    Texture *m_pFullTexture{};
    Texture *m_pEnemiesTexture{};
    Texture *m_pNameTexture{};
    Texture *m_pInteractablesTexture{};
    Vector2f m_SpawnPos{};
    int m_LevelCols{};
    int m_LevelRows{};

    std::vector<PolygonCollider> m_Colliders{};
    std::vector<Enemy *> m_Enemies{};
    std::vector<Interactable *> m_Interactables{};
    const SoundManager *m_pSoundManager{};
    BulletManager m_BulletManager{};
    Vector2f m_CursorPos{};
    float m_NameShownTimer{2.f};
};
