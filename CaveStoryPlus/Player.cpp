#include "pch.h"
#include "Player.h"
#include "Texture.h"

Player::Player()
	: m_pSpriteSheet(new Texture("player.png"))
{
}

Player::~Player()
{
	delete m_pSpriteSheet;
}

void Player::Draw() const
{
	const Rectf dest{ m_Position.x,m_Position.y,1.f,1.f };
	const Rectf source{ 0.f,0.f,m_CellSize,m_CellSize };
	m_pSpriteSheet->Draw(dest, source);
}

Vector2f Player::GetCameraFocusPos() const
{
	return m_Position + Vector2f(0.5f, 0.5f);
}
