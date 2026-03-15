#include "pch.h"
#include "Camera.h"
#include "Game.h"

void Camera::Begin(const Rectf& viewPort) const
{
	glPushMatrix();
	glTranslatef(viewPort.width * 0.5f, viewPort.height * 0.5f, 0.f);

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
