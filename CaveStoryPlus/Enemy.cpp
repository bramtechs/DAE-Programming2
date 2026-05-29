#include "Enemy.h"
#include "Texture.h"
#include "SoundManager.h"
#include "Player.h"
#include "pch.h"
#include "utils.h"

Enemy::Enemy(const Vector2f &size) : m_Size(size)
{
}

bool Enemy::TakeDamage(int damage)
{
    m_Health -= damage;
    if (m_pSoundManager)
    {
        m_pSoundManager->PlaySound(SoundManager::Effect::enemy_hurt);
    }

    return m_Health <= 0;
}

int Enemy::GetHealth() const
{
    return m_Health;
}

void Enemy::SetCenter(Vector2f position)
{
    m_Position = position;
}

Vector2f Enemy::GetCenter() const
{
    return m_Position;
}

Rectf Enemy::GetRegion() const
{
    Rectf r{};
    r.left = m_Position.x - m_Size.x * 0.5f;
    r.bottom = m_Position.y - m_Size.y * 0.5f;
    r.width = m_Size.x;
    r.height = m_Size.y;
    return r;
}

Circlef Enemy::GetCircleRegion() const
{
    return Circlef{GetCenter(), std::min(m_Size.x, m_Size.y) * 0.5f};
}

void Enemy::SetSpriteSheetTexture(const Texture &texture)
{
    m_pSpriteSheetTexture = &texture;
}

void Enemy::SetSoundManager(const SoundManager *pSoundManager)
{
    m_pSoundManager = pSoundManager;
}

void Enemy::InteractWithPlayer(Player &player)
{
    DealBodyDamage(player);
}

void Enemy::DealBodyDamage(Player &player)
{
    if (utils::IsOverlapping(GetRegion(), player.GetRegion()))
    {
        player.DealDamage(m_BodyDamage);
    }
}

void Enemy::DrawDebug() const
{
    utils::SetColor(Color4f{1.f, 0.f, 0.f, 1.f});
    utils::DrawRect(GetRegion());
}
