#include "pch.h"
#include "Player.h"
#include "utils.h"
#include "Level.h"
#include "utils.h"
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
        m_CurrentAnimationState = AnimState::walking;
        m_LookingLeft = false;
    }

    if (m_IsHoldingLeft)
    {
        const float boost{ m_Velocity.x > 0.f ? 2.f : 1.f };
        m_Velocity.x = std::max(-m_MaxHorizontalVelocity, m_Velocity.x - m_HorizontalMoveForce * delta * boost);
        m_CurrentAnimationState = AnimState::walking;
        m_LookingLeft = true;
    }

    if (!(m_IsHoldingLeft || m_IsHoldingRight))
    {
        m_Velocity.x = utils::EaseTowards(m_Velocity.x, 0.f, delta * m_DragForce);
        if (std::abs(m_Velocity.x) > 0.f)
        {
            m_CurrentAnimationState = AnimState::sliding;
        }
        else
        {
            m_CurrentAnimationState = AnimState::idle;
        }
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

        if (m_Velocity.y > 0)
        {
            m_CurrentAnimationState = AnimState::jumping;
        }
        else
        {
            m_CurrentAnimationState = AnimState::falling;
        }
    }

    m_Position += m_Velocity * delta;

    ProcessAnimationFrames(delta);
}

void Player::Draw() const
{
    const Rectf dest{ m_Position.x,m_Position.y,1.f,1.f };
    Rectf source{ 0.f,0.f,m_CellSize,m_CellSize };

    const int row{ m_LookingLeft ? 0 : 1 };
    source.left = source.width * m_CurrentAnimationFrame;
    source.bottom = source.height * row;

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

void Player::ProcessAnimationFrames(float delta)
{
    // player.png
    const int idleFrame{ 0 };
    const int walkStartFrame{ 0 };
    const int walkEndFrame{ 2 };
    const int jumpStartFrame{ 3 };
    const int jumpEndFrame{ 5 };
    const int fallFrame{ 6 };
    const int usingDoorFrame{ 7 };
    const int slideFrame{ 8 };

    switch (m_CurrentAnimationState)
    {

    case AnimState::idle:
        m_CurrentAnimationFrame = idleFrame;
        break;

    case AnimState::walking:
        ProcessAnimationState(AnimState::walking, walkStartFrame, walkEndFrame);
        break;

    case AnimState::sliding:
        m_CurrentAnimationFrame = slideFrame;
        break;

    case AnimState::jumping:
        ProcessAnimationState(AnimState::jumping, jumpStartFrame, jumpEndFrame);
        break;

    case AnimState::falling:
        m_CurrentAnimationFrame = fallFrame;
        break;

    case AnimState::usingdoor:
        m_CurrentAnimationFrame = usingDoorFrame;
        break;

    default:
        break;
    }


    m_AnimTimer += delta;
}

void Player::ProcessAnimationState(AnimState state, int startFrame, int endFrame)
{
    m_CurrentAnimationFrame = utils::Clamp(m_CurrentAnimationFrame, startFrame, endFrame);
    if (m_AnimTimer > m_TimePerFrame)
    {
        ++m_CurrentAnimationFrame;
        m_AnimTimer = 0.f;

        if (m_CurrentAnimationFrame > endFrame)
        {
            m_CurrentAnimationFrame = startFrame;
        }
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
