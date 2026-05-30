#include "pch.h"
#include "Camera.h"
#include "Game.h"
#include "utils.h"

#include <cmath>

Camera::Camera(const Rectf &viewPort) : m_ViewPort{viewPort}, m_Zoom{2.f}, m_MoveSpeed{10.f}, m_Center{}
{
}

void Camera::Begin() const
{
    glPushMatrix();
    glTranslatef(m_ViewPort.width * 0.5f, m_ViewPort.height * 0.5f, 0.f);

    const float combinedZoom{g_TileSize * m_Zoom};
    glScalef(combinedZoom, combinedZoom, 1.f);

    glTranslatef(-m_Center.x, -m_Center.y, 0.f);
}

void Camera::End() const
{
    glPopMatrix();
}

void Camera::SetCenter(const Vector2f &pos)
{
    m_Center = pos;
}

void Camera::MoveWithKeyboard(float delta)
{
    // Check keyboard state
    const Uint8 *pStates{SDL_GetKeyboardState(nullptr)};
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

    m_Center += move * delta * m_MoveSpeed;
}

void Camera::MoveTowards(const Vector2f &pos, float delta)
{
    // https://lisyarus.github.io/blog/posts/exponential-smoothing.html
    m_Center += (pos - m_Center) * (1.f - std::expf(-m_MoveSpeed * delta));
}

void Camera::ClampInside(const Rectf &clampBounds)
{
    const float combinedZoom{g_TileSize * m_Zoom};
    const float tileColsInViewport{m_ViewPort.width / combinedZoom};
    const float tileRowsInViewport{m_ViewPort.height / combinedZoom};

    const Rectf shrunkBounds{
        clampBounds.left + tileColsInViewport * 0.5f,
        clampBounds.bottom + tileRowsInViewport * 0.5f,
        std::max(0.f, clampBounds.width - tileColsInViewport),
        std::max(0.f, clampBounds.height - tileRowsInViewport),
    };

    m_Center.x = utils::Clamp(m_Center.x, shrunkBounds.left, shrunkBounds.GetRight());
    m_Center.y = utils::Clamp(m_Center.y, shrunkBounds.bottom, shrunkBounds.GetTop());
}

Vector2f Camera::ScreenToWorldPos(const Vector2f &screenPos) const
{
    const float combinedZoom{g_TileSize * m_Zoom};
    return Vector2f((screenPos.x - m_ViewPort.width * 0.5f) / combinedZoom + m_Center.x,
                    (screenPos.y - m_ViewPort.height * 0.5f) / combinedZoom + m_Center.y);
}

Rectf Camera::GetViewPort() const
{
    return m_ViewPort;
}
