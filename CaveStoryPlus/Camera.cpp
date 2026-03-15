#include "pch.h"
#include "Camera.h"
#include "Game.h"

Camera::Camera(const Rectf& viewPort)
	: m_Center{}, m_ViewPort{ viewPort }, m_Zoom{ 2.f }
{
}

void Camera::Begin() const
{
	glPushMatrix();
	glTranslatef(m_ViewPort.width * 0.5f, m_ViewPort.height * 0.5f, 0.f);

	const float combinedZoom{ g_TileSize * m_Zoom };
	glScalef(combinedZoom, combinedZoom, 1.f);

	glTranslatef(-m_Center.x, -m_Center.y, 0.f);

}

void Camera::End() const
{
	glPopMatrix();
}

void Camera::MoveWithKeyboard(float delta)
{
	// Check keyboard state
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	Vector2f move{};
	if (pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_D])
	{
		move.x += 1.f;
	}
	if (pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_A])
	{
		move.x -= 1.f;
	}
	if (pStates[SDL_SCANCODE_UP] || pStates[SDL_SCANCODE_W])
	{
		move.y += 1.f;
	}
	if (pStates[SDL_SCANCODE_DOWN] || pStates[SDL_SCANCODE_S])
	{
		move.y -= 1.f;
	}

	m_Center += move * delta * 10.f;
}

Vector2f Camera::ScreenToWorldPos(const Vector2f& screenPos) const
{
	const float combinedZoom{ g_TileSize * m_Zoom };
	return Vector2f(
		(screenPos.x - m_ViewPort.width * 0.5f) / combinedZoom + m_Center.x,
		(screenPos.y - m_ViewPort.height * 0.5f) / combinedZoom + m_Center.y
	);
}

Rectf Camera::GetViewPort() const
{
	return m_ViewPort;
}