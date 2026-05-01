#include "BulletManager.h"
#include "Bullet.h"
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
    auto it{m_Bullets.begin()};
    while (it != m_Bullets.end() && !killed)
    {
        if (it->IsOverlapping(enemy.GetRegion()))
        {
            killed = enemy.TakeDamage(it->GetDamage());
            it = m_Bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return killed;
}

void BulletManager::SpawnPolarStarBullet(const Vector2f &pos, float shootAngle)
{
    Bullet bullet{pos};
    bullet.SetVelocityFromAngle(shootAngle, 16.f);
    bullet.SetDamage(1.f);
    bullet.SetScale(0.025f);
    bullet.SetSourceRegion(Rectf{256.f, 78.f, 32.f, 4.f});

    m_Bullets.emplace_back(std::move(bullet));
}
