#include "pch.h"
#include "Player.h"
#include "utils.h"
#include "Level.h"
#include "Texture.h"

#include <iostream>

Player::Player()
	: m_pSpriteSheet(new Texture("player.png"))
{
}

Player::~Player()
{
	delete m_pSpriteSheet;
}

void Player::Update(float delta, const Level& level)
{
	bool isInsideFloor{};
	const Vector2f leftRayStart{ m_Position.x, m_Position.y + 1.f };
	const Vector2f leftRayEnd{ m_Position.x, m_Position.y - 1.f / m_CellSize };

	utils::HitInfo hit{};
	if (RaycastAgainstLevel(leftRayStart, leftRayEnd, level.GetColliders(), hit))
	{
		isInsideFloor = true;
	}
	else
	{
		const Vector2f rightRayStart{ leftRayStart.x + 1.f, leftRayStart.y };
		const Vector2f rightRayEnd{ leftRayEnd.x + 1.f, leftRayEnd.y };

		if (RaycastAgainstLevel(rightRayStart, rightRayEnd, level.GetColliders(), hit))
		{
			isInsideFloor = true;
		}
	}

	if (isInsideFloor)
	{
		m_Velocity.y = 0.f;
		m_Position.y = hit.intersectPoint.y;
	}
	else
	{
		m_Velocity.y += -m_Gravity * delta;
	}

	m_Position += m_Velocity * delta;

}

void Player::Draw() const
{
	const Rectf dest{ m_Position.x,m_Position.y,1.f,1.f };
	const Rectf source{ 0.f,0.f,m_CellSize,m_CellSize };
	m_pSpriteSheet->Draw(dest, source);
}

void Player::SetPosition(const Vector2f& pos)
{
	m_Position = pos;
}

void Player::SetPosition(float left, float bottom)
{
	m_Position.x = left;
	m_Position.y = bottom;
}

Vector2f Player::GetPosition() const
{
	return m_Position;
}

Vector2f Player::GetCameraFocusPosition() const
{
	return m_Position + Vector2f(0.5f, 0.5f);
}

bool Player::RaycastAgainstLevel(const Vector2f& start, const Vector2f& end, const Level::Colliders& colliders, utils::HitInfo& outHitInfo) const
{
	for (int i{}; i < colliders.size(); ++i)
	{
		if (utils::Raycast(colliders[i], start, end, outHitInfo))
		{
			return true;
		}
	}

	return false;
}
