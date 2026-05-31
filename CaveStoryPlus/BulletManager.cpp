#include "pch.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "Level.h"
#include "Enemy.h"
#include "utils.h"

BulletManager::BulletManager() : m_pTexture(new Texture("bullets.png")), m_Bullets()
{
}

BulletManager::~BulletManager()
{
    delete m_pTexture;
}

void BulletManager::Update(float delta)
{
    for (Bullet &bullet : m_Bullets)
    {
        bullet.Update(delta);
    }
}

void BulletManager::Draw() const
{
    for (const Bullet &bullet : m_Bullets)
    {
        bullet.Draw(*m_pTexture);
    }
}

bool BulletManager::InteractWithEnemy(Enemy &enemy)
{
    bool killed{};
    for (Bullet &bullet : m_Bullets)
    {
        if (bullet.IsActive() && bullet.IsOverlapping(enemy.GetRegion()))
        {
            if (!killed && enemy.TakeDamage(bullet.GetDamage()))
            {
                killed = true;
            }
            bullet.SetActive(false);
        }
    }

    return killed;
}

void BulletManager::InteractWithLevel(Level &level)
{
    for (int i{}; i < m_Bullets.size(); ++i)
    {
        for (const PolygonCollider &collider : level.GetColliders())
        {
            if (collider.Overlaps(m_Bullets[i].GetCircleRegion()))
            {
                m_Bullets[i].SetActive(false);
            }
        }
    }
}

void BulletManager::SpawnPolarStarBullet(const Vector2f &pos, float shootAngle)
{
    Bullet bullet{pos};
    bullet.SetVelocityFromAngle(shootAngle, 16.f);
    bullet.SetDamage(1);
    bullet.SetScale(0.025f);
    bullet.SetSourceRegion(Rectf{256.f, 78.f, 32.f, 4.f});

    // pool used bullets
    for (Bullet &existingBullet : m_Bullets)
    {
        if (!existingBullet.IsActive())
        {
            existingBullet = std::move(bullet);
            return;
        }
    }

    m_Bullets.emplace_back(std::move(bullet));
}
