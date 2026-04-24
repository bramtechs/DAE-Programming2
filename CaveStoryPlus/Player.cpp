#include "Player.h"
#include "Game.h"
#include "Level.h"
#include "Texture.h"
#include "pch.h"
#include "utils.h"

#include <cassert>
#include <iostream>

Player::Player() : m_pSpriteSheet(new Texture("player.png"))
{
}

Player::~Player()
{
    delete m_pSpriteSheet;
}

void Player::Update(float delta, const Level &level)
{
    if (m_IsHoldingRight)
    {
        // when going in opposite direction add more velocity for tighter movement
        const float boost{m_Velocity.x < 0.f ? 2.f : 1.f};
        m_Velocity.x = std::min(m_MaxHorizontalVelocity, m_Velocity.x + m_HorizontalMoveForce * delta * boost);
        m_LookingLeft = false;
        m_CurrentAnimationState = AnimState::walking;
    }

    if (m_IsHoldingLeft)
    {
        const float boost{m_Velocity.x > 0.f ? 2.f : 1.f};
        m_Velocity.x = std::max(-m_MaxHorizontalVelocity, m_Velocity.x - m_HorizontalMoveForce * delta * boost);
        m_LookingLeft = true;
        m_CurrentAnimationState = AnimState::walking;
    }

    const bool movingHorizontal{m_IsHoldingLeft || m_IsHoldingRight};
    if (!movingHorizontal)
    {
        m_Velocity.x = utils::EaseTowards(m_Velocity.x, 0.f, delta * m_DragForce);
    }

    if (m_Velocity.y > 0.f)
    {
        m_CurrentAnimationState = AnimState::jumping;
    }

    m_Position += m_Velocity * delta;

    if (m_Velocity.x < 0.f && CheckIfLeftInWall(level, m_Position.x, m_LastHitInfo))
    {
        m_Velocity.x = 0.f;
        m_Position.x = m_LastHitInfo.intersectPoint.x;
    }
    else if (m_Velocity.x > 0.f && CheckIfRightInWall(level, m_Position.x, m_LastHitInfo))
    {
        m_Velocity.x = 0.f;
        m_Position.x = m_LastHitInfo.intersectPoint.x - 1.f;
    }

    if (CheckIfInsideFloor(level, m_LastHitInfo) && not m_IsHoldingJump)
    {
        m_IsOnGround = true;
        m_Velocity.y = 0.f;
        m_Position.y = m_LastHitInfo.intersectPoint.y;
        if (!movingHorizontal && std::abs(m_Velocity.x) > 0.f)
        {
            m_CurrentAnimationState = AnimState::sliding;
        }
    }
    else
    {
        m_IsOnGround = false;
        m_Velocity.y += -m_Gravity * delta;

        if (m_Velocity.y > 0.f)
        {
            m_CurrentAnimationState = AnimState::jumping;
        }
        else
        {
            m_CurrentAnimationState = AnimState::falling;
        }
    }

    if (m_JumpWindowTimer > 0.f)
    {
        m_JumpWindowTimer -= delta;

        if (m_IsHoldingJump)
        {
            m_Velocity.y += m_JumpForce * delta * 2.3f;
            if (m_IsOnGround)
            {
                m_Position.y += 1.f / g_TileSize * 2.f; // ensure not in ground
            }
        }
    }

    ProcessAnimationFrames(delta);
}

void Player::Draw() const
{
    const Rectf dest{GetRegion()};
    Rectf source{0.f, 0.f, m_CellSize, m_CellSize};

    const int row{m_LookingLeft ? 0 : 1};
    source.left = source.width * m_CurrentAnimationFrame;
    source.bottom = source.height * row;

    m_pSpriteSheet->Draw(dest, source);

    utils::SetColor(Color4f{0.2f, 0.2f, 1.f, 1.f});
    utils::FillRect(utils::RectWithCenter(m_Position, 0.1f));

    utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
    utils::FillRect(utils::RectWithCenter(m_LastHitInfo.intersectPoint, 0.1f));
}

void Player::SetPosition(const Vector2f &pos)
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

Rectf Player::GetRegion() const
{
    return Rectf{m_Position.x, m_Position.y, 1.f, 1.f};
}

void Player::HandleKeyDownEvent(const SDL_KeyboardEvent &e)
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
        m_IsHoldingJump = true;
        if (m_IsOnGround)
        {
            // apply initial jump impulse
            m_Velocity.y += m_JumpForce;
            m_JumpWindowTimer = m_JumpWindow;
        }
        break;
    }
}

void Player::HandleKeyUpEvent(const SDL_KeyboardEvent &e)
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
    case SDLK_SPACE:
    case SDLK_z:
        m_IsHoldingJump = false;
        break;
    }
}

void Player::ProcessAnimationFrames(float delta)
{
    // player.png
    const int idleFrame{0};
    const int walkStartFrame{0};
    const int walkEndFrame{1};
    const int fallingFrame{1};
    const int jumpingFrame{2};
    const int usingDoorFrame{7};
    const int slideFrame{8};

    switch (m_CurrentAnimationState)
    {

    case AnimState::idle:
        m_CurrentAnimationFrame = idleFrame;
        break;

    case AnimState::walking:
        ProcessAnimationState(AnimState::walking, walkStartFrame, walkEndFrame);
        break;

    case AnimState::jumping:
        m_CurrentAnimationFrame = jumpingFrame;
        break;

    case AnimState::falling:
        m_CurrentAnimationFrame = fallingFrame;
        break;

    case AnimState::sliding:
        m_CurrentAnimationFrame = slideFrame;
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

bool Player::RaycastAgainstLevel(const Vector2f &start, const Vector2f &end,
                                 const std::vector<PolygonCollider> &colliders, utils::HitInfo &outHitInfo) const
{
    for (int i{}; i < colliders.size(); ++i)
    {
        const std::vector<Vector2f> &vertices{colliders[i].GetPolygon()};
        if (utils::Raycast(vertices, start, end, outHitInfo))
        {
            return true;
        }
    }

    return false;
}

bool Player::CheckIfLeftInWall(const Level &level, float positionX, utils::HitInfo &outHitInfo) const
{
    const float inset{1.f / m_CellSize};

    const Vector2f botRayStart{positionX, m_Position.y + inset};
    const Vector2f botRayEnd{positionX + inset, m_Position.y + inset};
    if (CheckRaycast(level, botRayStart, botRayEnd, outHitInfo))
    {
        return true;
    }

    const Vector2f topRayStart{positionX, m_Position.y + 1.f - inset};
    const Vector2f topRayEnd{positionX + inset, m_Position.y + 1.f - inset};
    if (CheckRaycast(level, topRayStart, topRayEnd, outHitInfo))
    {
        return true;
    }

    return false;
}

bool Player::CheckIfRightInWall(const Level &level, float positionX, utils::HitInfo &outHitInfo) const
{
    const float inset{1.f / m_CellSize};

    const Vector2f botRayStart{positionX + 1.f, m_Position.y + inset};
    const Vector2f botRayEnd{positionX + 1.f - inset, m_Position.y + inset};
    if (CheckRaycast(level, botRayStart, botRayEnd, outHitInfo))
    {
        return true;
    }

    const Vector2f topRayStart{positionX + 1.f, m_Position.y + 1.f - inset};
    const Vector2f topRayEnd{positionX + 1.f - inset, m_Position.y + 1.f - inset};
    if (CheckRaycast(level, topRayStart, topRayEnd, outHitInfo))
    {
        return true;
    }

    return false;
}

bool Player::CheckIfInsideFloor(const Level &level, utils::HitInfo &outHitInfo) const
{
    const float inset{1.f / m_CellSize};

    const Vector2f leftRayStart{m_Position.x, m_Position.y + 1.f};
    const Vector2f leftRayEnd{m_Position.x, m_Position.y - inset};
    if (CheckRaycast(level, leftRayStart, leftRayEnd, outHitInfo))
    {
        return true;
    }

    const Vector2f rightRayStart{leftRayStart.x + 1.f, leftRayStart.y};
    const Vector2f rightRayEnd{leftRayEnd.x + 1.f - inset, leftRayEnd.y};
    if (CheckRaycast(level, rightRayStart, rightRayEnd, outHitInfo))
    {
        return true;
    }

    return false;
}

bool Player::CheckRaycast(const Level &level, const Vector2f &start, const Vector2f &end,
                          utils::HitInfo &outHitInfo) const
{
    return RaycastAgainstLevel(start, end, level.GetColliders(), outHitInfo);
}
