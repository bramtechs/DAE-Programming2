#include "Enemy.h"
#include "Texture.h"
#include "Player.h"
#include "pch.h"
#include "utils.h"

int Enemy::m_InstanceCount{0};
Texture *Enemy::m_pSpriteSheetTexture{};

Enemy::Enemy(const Vector2f &size) : m_Size(size)
{
    if (m_InstanceCount == 0)
    {
        m_pSpriteSheetTexture = new Texture("NpcCemet.bmp");
    }

    ++m_InstanceCount;
}

Enemy::~Enemy()
{
    --m_InstanceCount;

    if (m_InstanceCount == 0)
    {
        delete m_pSpriteSheetTexture;
    }
}

bool Enemy::TakeDamage(int damage)
{
    m_Health -= damage;
    return m_Health <= 0;
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

void Enemy::InteractWithPlayer(Player& player)
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
