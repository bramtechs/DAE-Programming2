#include "pch.h"
#include "Player.h"
#include "utils.h"
#include "Level.h"
#include "Texture.h"
#include "Game.h"

#include <iostream>
#include <cassert>

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
    if (m_IsHoldingRight)
    {
        // when going in opposite direction add more velocity for tighter movement
        const float boost{ m_Velocity.x < 0.f ? 2.f : 1.f };
        m_Velocity.x = std::min(m_MaxHorizontalVelocity, m_Velocity.x + m_HorizontalMoveForce * delta * boost);
    }

    if (m_IsHoldingLeft)
    {
        const float boost{ m_Velocity.x > 0.f ? 2.f : 1.f };
        m_Velocity.x = std::max(-m_MaxHorizontalVelocity, m_Velocity.x - m_HorizontalMoveForce * delta * boost);
    }

    if (!(m_IsHoldingLeft || m_IsHoldingRight))
    {
        m_Velocity.x = utils::EaseTowards(m_Velocity.x, 0.f, delta * m_DragForce);
    }

    utils::HitInfo hit{};
    if (CheckIfInsideFloor(level, hit))
    {
        m_IsOnGround = true;
        m_Velocity.y = 0.f;
        m_Position.y = hit.intersectPoint.y;
    }
    else
    {
        m_IsOnGround = false;
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

void Player::HandleKeyDownEvent(const SDL_KeyboardEvent& e)
{
    switch (e.keysym.sym)
    {
    case SDLK_d:
    case SDLK_RIGHT:
        m_IsHoldingRight = true;
        break;
    case SDLK_a:
    case SDLK_LEFT:
        m_IsHoldingLeft = true;
        break;
    case SDLK_z:
    case SDLK_SPACE:
        TryJump();
        break;
    }
}

void Player::HandleKeyUpEvent(const SDL_KeyboardEvent& e)
{
    switch (e.keysym.sym)
    {
    case SDLK_d:
    case SDLK_RIGHT:
        m_IsHoldingRight = false;
        break;
    case SDLK_a:
    case SDLK_LEFT:
        m_IsHoldingLeft = false;
        break;
    }
}

void Player::TryJump()
{
    if (m_IsOnGround)
    {
        m_Velocity.y = m_JumpForce;
        m_Position.y += 1.f / g_TileSize * 2.f; // ensure not in ground
    }
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

bool Player::CheckIfInsideFloor(const Level& level, utils::HitInfo& outHitInfo) const
{
    bool isInsideFloor{};
    const Vector2f leftRayStart{ m_Position.x, m_Position.y + 1.f };
    const Vector2f leftRayEnd{ m_Position.x, m_Position.y - 1.f / m_CellSize };

    if (RaycastAgainstLevel(leftRayStart, leftRayEnd, level.GetColliders(), outHitInfo))
    {
        isInsideFloor = true;
    }
    else
    {
        const Vector2f rightRayStart{ leftRayStart.x + 1.f, leftRayStart.y };
        const Vector2f rightRayEnd{ leftRayEnd.x + 1.f, leftRayEnd.y };

        if (RaycastAgainstLevel(rightRayStart, rightRayEnd, level.GetColliders(), outHitInfo))
        {
            isInsideFloor = true;
        }
    }

    return isInsideFloor;
}
