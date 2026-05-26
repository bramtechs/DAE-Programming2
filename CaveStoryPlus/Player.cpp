#include "Player.h"
#include "BulletManager.h"
#include "DialogManager.h"
#include "Game.h"
#include "Level.h"
#include "PolarStar.h"
#include "SDL_keyboard.h"
#include "Texture.h"
#include "Weapon.h"
#include "PlayerGUI.h"
#include "pch.h"
#include "utils.h"

#include <cassert>
#include <iostream>

Player::Player(DialogManager &dialog)
    : m_pSpriteSheet(new Texture("player.png")), m_pGUI(new PlayerGUI(*this)), m_DialogManager(dialog)
{
}

Player::~Player()
{
    delete m_pSpriteSheet;
    delete m_pHeldWeapon;
    delete m_pGUI;
}

void Player::Update(float delta, Level &level)
{
    if (m_Health <= 0)
    {
        return;
    }

    UpdateMovement(delta, level);
    UpdateAnimationFrames(delta);
    UpdateShooting(delta, level);

    m_InvincibilityTimer -= delta;

    if (m_SecondsSinceOxygenDrain > 0.5f)
    {
        m_Oxygen = m_MaxOxygen;
    }
    m_SecondsSinceOxygenDrain += delta;

    m_pGUI->UpdateTimers(delta);
    m_pGUI->UpdateValues();
}

void Player::UpdateMovement(float delta, Level &level)
{
    const Uint8 *const pStates{SDL_GetKeyboardState(nullptr)};
    bool holdingLeft{};
    bool holdingRight{};
    if (pStates[SDL_SCANCODE_RIGHT])
    {
        // when going in opposite direction add more velocity for tighter movement
        const float boost{m_Velocity.x < 0.f ? 2.f : 1.f};
        m_Velocity.x = std::min(m_MaxHorizontalVelocity, m_Velocity.x + m_HorizontalMoveForce * delta * boost);
        m_LookingLeft = false;
        m_CurrentAnimationState = AnimState::walking;
        m_WeaponOrientation = Weapon::Orientation::east;
        holdingRight = true;
    }

    if (pStates[SDL_SCANCODE_LEFT])
    {
        const float boost{m_Velocity.x > 0.f ? 2.f : 1.f};
        m_Velocity.x = std::max(-m_MaxHorizontalVelocity, m_Velocity.x - m_HorizontalMoveForce * delta * boost);
        m_LookingLeft = true;
        m_CurrentAnimationState = AnimState::walking;
        m_WeaponOrientation = Weapon::Orientation::west;
        holdingLeft = true;
    }

    const bool movingHorizontal{holdingLeft || holdingRight};
    if (!movingHorizontal)
    {
        m_Velocity.x = utils::EaseTowards(m_Velocity.x, 0.f, delta * m_DragForce);
    }

    if (m_Velocity.y > 0.f)
    {
        m_CurrentAnimationState = AnimState::jumping;
    }

    utils::HitInfo hit{};

    const float movementX{m_Velocity.x * delta};
    const float inset{m_HitboxWidth / m_CellSize};
    if (movementX < 0.f && CheckIfHitsLeftWall(level, movementX, hit))
    {
        m_Velocity.x = 0.f;
        m_Position.x = hit.intersectPoint.x + inset;
    }
    else if (movementX > 0.f && CheckIfHitsRightWall(level, movementX, hit))
    {
        m_Velocity.x = 0.f;
        m_Position.x = hit.intersectPoint.x - m_HitboxWidth - inset;
    }
    else
    {
        m_Position.x += movementX;
    }

    const float movementY{m_Velocity.y * delta};
    if (movementY < 0.f && CheckIfHitsFloor(level, movementY, hit))
    {
        m_IsOnGround = true;
        m_Velocity.y = 0.f;
        m_Position.y = hit.intersectPoint.y;
        if (!movingHorizontal && std::abs(m_Velocity.x) > 0.f)
        {
            m_CurrentAnimationState = AnimState::sliding;
        }
    }
    else if (movementY > 0.f && CheckIfHitsCeiling(level, movementY, hit))
    {
        m_IsOnGround = false;
        m_Velocity.y = 0.f;
        m_Position.y = hit.intersectPoint.y - m_HitboxHeight - inset;
    }
    else
    {
        m_Position.y += movementY;
        m_IsOnGround = movementY <= 0.f && CheckIfOnGround(level, hit);

        if (!m_IsOnGround)
        {
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
        else
        {
            m_Velocity.y = 0.f;
        }
    }

    if (m_JumpWindowTimer > 0.f)
    {
        m_JumpWindowTimer -= delta;

        if (pStates[SDL_SCANCODE_Z])
        {
            m_Velocity.y += m_JumpForce * delta * 2.3f;
            if (m_IsOnGround)
            {
                m_Position.y += m_HitboxHeight / g_TileSize * 2.f; // ensure not in ground
            }
        }
    }
}

void Player::UpdateShooting(float delta, Level &level)
{
    const Uint8 *const pStates{SDL_GetKeyboardState(nullptr)};
    if (pStates[SDL_SCANCODE_X])
    {
        if (m_pHeldWeapon && m_LastShootTimer > m_pHeldWeapon->GetShootIntervalSeconds())
        {
            m_pHeldWeapon->Shoot(GetHandPosition(), m_WeaponOrientation, level.GetBulletManager());
            m_LastShootTimer = 0.f;
        }
    }

    m_LastShootTimer += delta;
}

void Player::Draw() const
{
    if (m_Health <= 0)
    {
        return;
    }

    float flashTime{m_FlashInterval};
    if (m_InvincibilityTimer > 0.f)
    {
        flashTime = std::fmod(m_InvincibilityTimer, m_FlashInterval);
    }

    if (flashTime > m_FlashInterval * 0.5f)
    {
        const Rectf dest{GetRegion()};
        Rectf source{0.f, 0.f, m_CellSize, m_CellSize};

        const int row{m_LookingLeft ? 0 : 1};
        source.left = source.width * m_CurrentAnimationFrame;
        source.bottom = source.height * row;
        m_pSpriteSheet->Draw(dest, source);

        if (m_pHeldWeapon)
        {
            m_pHeldWeapon->Draw(GetHandPosition(), m_WeaponOrientation);
        }
    }
}

void Player::DrawGUI(const Rectf &viewport) const
{
    m_pGUI->Draw(viewport);
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

Vector2f Player::GetHandPosition() const
{
    const float xPadding{0.1f};
    const Vector2f handPosOffset{m_LookingLeft ? xPadding : 1.f - xPadding, 0.5f};
    return m_Position + handPosOffset;
}

Vector2f Player::GetCameraFocusPosition() const
{
    return m_Position + Vector2f(0.5f, 0.5f);
}

Rectf Player::GetRegion() const
{
    return Rectf{m_Position.x, m_Position.y, 1.f, 1.f};
}

void Player::HoldWeapon(Weapon *pWeapon)
{
    delete m_pHeldWeapon;
    m_pHeldWeapon = pWeapon;
}

void Player::HandleKeyDownEvent(const SDL_KeyboardEvent &e)
{
    switch (e.keysym.sym)
    {
    case SDLK_UP:
        m_WeaponOrientation = Weapon::Orientation::north;
        break;
    case SDLK_DOWN:
        m_WeaponOrientation = Weapon::Orientation::south;
        break;
    case SDLK_z:
        if (m_IsOnGround)
        {
            // apply initial jump impulse
            m_Velocity.y += m_JumpForce;
            m_IsOnGround = false;
            m_JumpWindowTimer = m_JumpWindow;
        }
        break;

#ifndef NDEBUG
    case SDLK_F4:
        // cheat to get the Polar Star early
        HoldWeapon(new PolarStar());
        break;
#endif

    default:
        break;
    }
}

void Player::HandleKeyUpEvent(const SDL_KeyboardEvent &e)
{
    switch (e.keysym.sym)
    {
    case SDLK_UP:
        if (m_WeaponOrientation == Weapon::Orientation::north)
        {
            m_WeaponOrientation = m_LookingLeft ? Weapon::Orientation::west : Weapon::Orientation::east;
        }
        break;
    case SDLK_DOWN:
        if (m_WeaponOrientation == Weapon::Orientation::south)
        {
            m_WeaponOrientation = m_LookingLeft ? Weapon::Orientation::west : Weapon::Orientation::east;
        }
        break;
    default:
        break;
    }
}

void Player::DealDamage(int damage)
{
    if (m_InvincibilityTimer <= 0.f)
    {
        m_Health -= damage;
        m_pGUI->UpdateValues();
        m_InvincibilityTimer = m_InvincibilityOnHitSeconds;
        std::cout << "Dealt " << damage << " damage to player!" << std::endl;

        if (m_Health <= 0)
        {
            m_DialogManager.QueueMessage({"You have died."});
            DialogMessage &msg{m_DialogManager.QueueMessage({"Want to retry?"})};
            msg.SetReadEvent(new RespawnDialogEvent());
        }
    }
}

void Player::RespawnDialogEvent::Execute(Game &game)
{
    game.Restart();
}

void Player::DrainOxygen()
{
    m_Oxygen = std::max(m_Oxygen - 1, 0);
    m_SecondsSinceOxygenDrain = 0.f;
    if (m_Oxygen <= 0)
    {
        DealDamage(1);
    }
}

bool Player::HasMaximumOxygen() const
{
    return m_Oxygen >= 100;
}

bool Player::HasMaximumHealth() const
{
    return m_Health >= m_MaxHealth;
}

void Player::AddGold(int amount)
{
    m_Gold += amount;
    while (m_Gold >= GetGoldNeededForLevel(m_Level + 1))
    {
        ++m_Level;
        m_pGUI->OnLevelUp();
    }
}

void Player::AddHealth(int amount)
{
    m_Health = std::min(amount + 1, m_MaxHealth);
}

int Player::GetGoldNeededForLevel(int level)
{
    if (level <= 0)
    {
        return 0;
    }

    // 5 * 2^(level-1)
    return 5 << (level - 1);
}

void Player::AddMaxHealth(int amount)
{
    m_MaxHealth += amount;
    m_Health += amount;
}

void Player::UpdateAnimationFrames(float delta)
{
    if (m_Velocity.Length() < 0.01f)
    {
        m_CurrentAnimationFrame = 0;
        return;
    }

    switch (m_CurrentAnimationState)
    {

    case AnimState::idle: {
        m_CurrentAnimationFrame = 0;
        break;
    }

    case AnimState::walking: {
        const int walkStartFrame{0};
        const int walkEndFrame{1};
        UpdateAnimationState(AnimState::walking, walkStartFrame, walkEndFrame);
        break;
    }

    case AnimState::jumping: {
        m_CurrentAnimationFrame = 2;
        break;
    }
    case AnimState::falling: {
        m_CurrentAnimationFrame = 1;
        break;
    }
    case AnimState::sliding: {
        m_CurrentAnimationFrame = 8;
        break;
    }
    case AnimState::usingdoor: {
        m_CurrentAnimationFrame = 7;
        break;
    }
    default:
        break;
    }

    m_AnimTimer += delta;
}

void Player::UpdateAnimationState(AnimState state, int startFrame, int endFrame)
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
                                 const std::vector<PolygonCollider> &colliders, const Vector2f &collisionAxis,
                                 utils::HitInfo &outHitInfo) const
{
    bool hasHit{};

    for (int i{}; i < colliders.size(); ++i)
    {
        const std::vector<Vector2f> &vertices{colliders[i].GetPolygon()};
        for (int idx{}; idx < vertices.size(); ++idx)
        {
            const Vector2f q1{vertices[idx]};
            const Vector2f q2{vertices[(idx + 1) % vertices.size()]};

            float lambda1{};
            float lambda2{};
            if (utils::IntersectLineSegments(start, end, q1, q2, lambda1, lambda2) && lambda1 > 0.f && lambda1 <= 1.f &&
                lambda2 > 0.f && lambda2 <= 1.f)
            {
                utils::HitInfo hit{};
                hit.lambda = lambda1;
                hit.intersectPoint =
                    Vector2f{start.x + ((end.x - start.x) * lambda1), start.y + ((end.y - start.y) * lambda1)};
                hit.normal = Vector2f{q2 - q1}.Orthogonal().Normalized();

                if (std::abs(hit.normal.DotProduct(collisionAxis)) > 0.5f &&
                    (!hasHit || hit.lambda < outHitInfo.lambda))
                {
                    hasHit = true;
                    outHitInfo = hit;
                }
            }
        }
    }

    return hasHit;
}

bool Player::CheckIfHitsLeftWall(const Level &level, float movementX, utils::HitInfo &outHitInfo) const
{
    const float inset{m_HitboxWidth / m_CellSize};
    const Vector2f collisionAxis{1.f, 0.f};

    const Vector2f botRayStart{m_Position.x + inset, m_Position.y + inset};
    const Vector2f botRayEnd{m_Position.x + movementX - inset, m_Position.y + inset};
    const Vector2f topRayStart{m_Position.x + inset, m_Position.y + m_HitboxHeight - inset};
    const Vector2f topRayEnd{m_Position.x + movementX - inset, m_Position.y + m_HitboxHeight - inset};

    return CheckRaycastPair(level, botRayStart, botRayEnd, topRayStart, topRayEnd, collisionAxis, outHitInfo);
}

bool Player::CheckIfHitsRightWall(const Level &level, float movementX, utils::HitInfo &outHitInfo) const
{
    const float inset{m_HitboxWidth / m_CellSize};
    const Vector2f collisionAxis{1.f, 0.f};

    const Vector2f botRayStart{m_Position.x + m_HitboxWidth - inset, m_Position.y + inset};
    const Vector2f botRayEnd{m_Position.x + m_HitboxWidth + movementX + inset, m_Position.y + inset};
    const Vector2f topRayStart{m_Position.x + m_HitboxWidth - inset, m_Position.y + m_HitboxHeight - inset};
    const Vector2f topRayEnd{m_Position.x + m_HitboxWidth + movementX + inset, m_Position.y + m_HitboxHeight - inset};

    return CheckRaycastPair(level, botRayStart, botRayEnd, topRayStart, topRayEnd, collisionAxis, outHitInfo);
}

bool Player::CheckIfOnGround(const Level &level, utils::HitInfo &outHitInfo) const
{
    const float inset{1.f / m_CellSize};
    return CheckIfHitsFloor(level, -inset, outHitInfo);
}

bool Player::CheckIfHitsFloor(const Level &level, float movementY, utils::HitInfo &outHitInfo) const
{
    const float inset{m_HitboxWidth / m_CellSize};
    const Vector2f collisionAxis{0.f, 1.f};

    const Vector2f leftRayStart{m_Position.x + inset, m_Position.y + inset};
    const Vector2f leftRayEnd{m_Position.x + inset, m_Position.y + movementY - inset};
    const Vector2f rightRayStart{m_Position.x + m_HitboxWidth - inset, m_Position.y + inset};
    const Vector2f rightRayEnd{m_Position.x + m_HitboxWidth - inset, m_Position.y + movementY - inset};

    return CheckRaycastPair(level, leftRayStart, leftRayEnd, rightRayStart, rightRayEnd, collisionAxis, outHitInfo);
}

bool Player::CheckIfHitsCeiling(const Level &level, float movementY, utils::HitInfo &outHitInfo) const
{
    const float inset{1.f / m_CellSize};
    const Vector2f collisionAxis{0.f, 1.f};

    const Vector2f leftRayStart{m_Position.x + inset, m_Position.y + m_HitboxHeight - inset};
    const Vector2f leftRayEnd{m_Position.x + inset, m_Position.y + m_HitboxHeight + movementY + inset};
    const Vector2f rightRayStart{m_Position.x + m_HitboxWidth - inset, m_Position.y + m_HitboxHeight - inset};
    const Vector2f rightRayEnd{m_Position.x + m_HitboxWidth - inset, m_Position.y + m_HitboxHeight + movementY + inset};

    return CheckRaycastPair(level, leftRayStart, leftRayEnd, rightRayStart, rightRayEnd, collisionAxis, outHitInfo);
}

bool Player::CheckRaycast(const Level &level, const Vector2f &start, const Vector2f &end, const Vector2f &collisionAxis,
                          utils::HitInfo &outHitInfo) const
{
    /*
    GizmoManager::LineGizmo gizmo{};
    gizmo.start = start;
    gizmo.end = end;
    m_GizmoManager.QueueGizmo(gizmo);
    */
    bool hit{RaycastAgainstLevel(start, end, level.GetColliders(), collisionAxis, outHitInfo)};
    if (!hit)
    {
        hit = RaycastAgainstLevel(start, end, level.GetSolidEnemyColliders(), collisionAxis, outHitInfo);
    }
    return hit;
}

bool Player::CheckRaycastPair(const Level &level, const Vector2f &firstStart, const Vector2f &firstEnd,
                              const Vector2f &secondStart, const Vector2f &secondEnd, const Vector2f &collisionAxis,
                              utils::HitInfo &outHitInfo) const
{
    const bool firstHit{CheckRaycast(level, firstStart, firstEnd, collisionAxis, outHitInfo)};

    utils::HitInfo secondHit{};
    const bool secondHasHit{CheckRaycast(level, secondStart, secondEnd, collisionAxis, secondHit)};
    if (secondHasHit && (!firstHit || secondHit.lambda < outHitInfo.lambda))
    {
        outHitInfo = secondHit;
    }

    return firstHit || secondHasHit;
}

float Player::GetLevelProgress() const
{
    const int prevNeeded{GetGoldNeededForLevel(m_Level)};
    const int nextNeeded{GetGoldNeededForLevel(m_Level + 1)};
    return (m_Gold - prevNeeded) / static_cast<float>(nextNeeded - prevNeeded);
}
