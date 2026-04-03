#include "pch.h"
#include "Enemy.h"
#include "utils.h"

Enemy::Enemy(const Vector2f& size)
	: m_Size(size)
{
}

void Enemy::SetPosition(Vector2f position)
{
	m_Position = position;
}

Vector2f Enemy::GetPosition() const
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

void Enemy::DrawDebug() const
{
	utils::SetColor(Color4f{ 1.f,0.f,0.f,1.f });
	utils::FillRect(GetRegion());
}
