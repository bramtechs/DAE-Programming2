#pragma once
#include "BulletManager.h"
#include "PolygonCollider.h"
#include "Game.h"
#include "structs.h"

#include <string>
#include <vector>

class Interactable;
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
                   const Vector2f &spawnPos);
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

    Rectf GetBounds() const;

    const std::vector<PolygonCollider> GetSolidEnemyColliders() const;

    const std::vector<PolygonCollider> &GetColliders() const
    {
        return m_Colliders;
    }

    std::vector<PolygonCollider> &GetColliders()
    {
        return m_Colliders;
    }

    std::string GetCollidersFilePath() const
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

  private:
    static constexpr float m_BgTextureScale{g_TileSize / 2.f};

    void SpawnEnemyCollectibles(const Enemy& enemy, bool playerIsDamaged);

    void DrawTileGrid() const;
    void DrawColliders() const;

    Texture *m_pFullTexture{};
    std::string m_CollidersPath{};
    std::vector<PolygonCollider> m_Colliders{};
    std::vector<Enemy *> m_Enemies{};
    std::vector<Interactable *> m_Interactables{};
    BulletManager m_BulletManager{};
    Texture *m_pNameTexture{};
    Vector2f m_CursorPos{};
    Vector2f m_SpawnPos{};
    float m_NameShownTimer{2.f};
    int m_LevelCols{};
    int m_LevelRows{};
};
