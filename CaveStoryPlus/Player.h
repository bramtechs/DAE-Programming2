#pragma once
#include "GizmoManager.h"
#include "Level.h"
#include "Vector2f.h"
#include "Weapon.h"
#include "utils.h"

#include <SDL_events.h>

class Texture;
class Weapon;
class DialogManager;
class BulletManager;
class Player
{
  public:
    explicit Player(DialogManager &dialogs);
    ~Player();

    void Update(float delta, Level &level);
    void Draw() const;

    void SetPosition(const Vector2f &pos);
    void SetPosition(float left, float bottom);

    void HandleKeyDownEvent(const SDL_KeyboardEvent &e);
    void HandleKeyUpEvent(const SDL_KeyboardEvent &e);

    void DealDamage(int amount);

    void AddGold(int amount = 1);
    void AddMaxHealth(int amount);
    void HoldWeapon(Weapon *pWeapon);

    template <typename T> bool IsHoldingWeapon() const
    {
        static_assert(std::is_base_of_v<Weapon, T>, "T needs to have base Weapon");
        return dynamic_cast<T *>(m_pHeldWeapon) != nullptr;
    }

    Vector2f GetPosition() const;

    Vector2f GetHandPosition() const;

    Vector2f GetCameraFocusPosition() const;

    Rectf GetRegion() const;

    int GetHealth() const;
    int GetMaxHealth() const;

  private:
    enum class AnimState
    {
        idle,
        walking,
        jumping,
        falling,
        sliding,
        usingdoor,
    };

    void UpdateAnimationFrames(float delta);
    void UpdateAnimationState(AnimState state, int startFrame, int endFrame);
    void UpdateMovement(float delta, Level &level);
    void UpdateShooting(float delta, Level &level);

    bool RaycastAgainstLevel(const Vector2f &start, const Vector2f &end, const std::vector<PolygonCollider> &colliders,
                             const Vector2f &collisionAxis, utils::HitInfo &outHitInfo) const;

    bool CheckRaycast(const Level &level, const Vector2f &start, const Vector2f &end, const Vector2f &collisionAxis,
                      utils::HitInfo &outHitInfo) const;
    bool CheckRaycastPair(const Level &level, const Vector2f &firstStart, const Vector2f &firstEnd,
                          const Vector2f &secondStart, const Vector2f &secondEnd, const Vector2f &collisionAxis,
                          utils::HitInfo &outHitInfo) const;
    bool CheckIfOnGround(const Level &level, utils::HitInfo &outHitInfo) const;
    bool CheckIfHitsFloor(const Level &level, float movementY, utils::HitInfo &outHitInfo) const;
    bool CheckIfHitsCeiling(const Level &level, float movementY, utils::HitInfo &outHitInfo) const;
    bool CheckIfHitsLeftWall(const Level &level, float movementX, utils::HitInfo &outHitInfo) const;
    bool CheckIfHitsRightWall(const Level &level, float movementX, utils::HitInfo &outHitInfo) const;

    constexpr static float m_HitboxHeight{0.8f};
    constexpr static float m_HitboxWidth{0.75f};
    constexpr static float m_CellSize{32.f};
    constexpr static float m_TimePerFrame{0.15f};
    constexpr static int m_SpriteSheetCols{11};
    constexpr static int m_SpriteSheetRows{2};
    constexpr static float m_FlashInterval{0.2f};
    constexpr static float m_InvincibilityOnHitSeconds{2.f};

    // time to hold space for maximum jump power
    constexpr static float m_JumpWindow{0.5f};

    Vector2f m_Position{0.f, 0.f};
    Vector2f m_Velocity{};

    Texture *m_pSpriteSheet{};
    AnimState m_CurrentAnimationState{AnimState::idle};
    Weapon::Orientation m_WeaponOrientation{Weapon::Orientation::east};
    Weapon *m_pHeldWeapon{};
    DialogManager &m_DialogManager;

    float m_HorizontalMoveForce{24.f};
    float m_MaxHorizontalVelocity{4.f};
    float m_DragForce{20.f};
    float m_JumpForce{4.5f};
    float m_Gravity{9.81f};
    float m_AnimTimer{0.f};
    float m_JumpWindowTimer{0.1f};
    float m_LastShootTimer{};
    float m_InvincibilityTimer{};

    int m_CurrentAnimationFrame{};
    int m_Gold{};
    int m_MaxHealth{3};
    int m_Health{m_MaxHealth};

    bool m_LookingLeft{};
    bool m_IsOnGround{};
};
