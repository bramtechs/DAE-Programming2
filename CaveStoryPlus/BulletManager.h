#pragma once
#include "Texture.h"

#include <vector>

class Enemy;
class Bullet;
class BulletManager final
{
  public:
    BulletManager();
    ~BulletManager();

    BulletManager(const BulletManager &) = delete;
    BulletManager(BulletManager &&) noexcept = delete;

    BulletManager &operator=(const BulletManager &) = delete;
    BulletManager &operator=(BulletManager &&) noexcept = delete;

    void Update(float delta);
    void Draw() const;

    // returns true if enemy killed
    bool InteractWithEnemy(Enemy &enemy);

    void SpawnPolarStarBullet(const Vector2f &pos, float shootAngle);

  private:
    Texture *m_pTexture;
    std::vector<Bullet> m_Bullets;
};
