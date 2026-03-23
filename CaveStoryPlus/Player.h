#pragma once
#include "utils.h"
#include "Vector2f.h"
#include "Level.h"

class Texture;
class Player
{
public:
    Player();
    ~Player();

    void Update(float delta, const Level& level);
    void Draw() const;

    void SetPosition(const Vector2f& pos);
    void SetPosition(float left, float bottom);

    Vector2f GetPosition() const;

    Vector2f GetCameraFocusPosition() const;

    void HandleKeyDownEvent(const SDL_KeyboardEvent& e);

    void HandleKeyUpEvent(const SDL_KeyboardEvent& e);

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

    void TryJump();
    void ProcessAnimationFrames(float delta);
    void ProcessAnimationState(AnimState state, int startFrame, int endFrame);

    bool RaycastAgainstLevel(const Vector2f& start, const Vector2f& end, const Level::Colliders& colliders, utils::HitInfo& outHitInfo) const;

    bool CheckIfInsideFloor(const Level& level, utils::HitInfo& outHitInfo) const;

    constexpr static float m_CellSize{ 32.f };
    constexpr static int m_SpriteSheetCols{ 11 };
    constexpr static int m_SpriteSheetRows{ 2 };
    constexpr static float m_TimePerFrame{ 0.15f };

    Texture* m_pSpriteSheet{};
    Vector2f m_Position{ 37.f, 33.f };
    Vector2f m_Velocity{};
    float m_HorizontalMoveForce{ 24.f };
    float m_MaxHorizontalVelocity{ 4.f };
    float m_DragForce{ 20.f };
    float m_JumpForce{ 6.f };
    float m_Gravity{ 9.81f };
    AnimState m_CurrentAnimationState{ AnimState::idle };
    int m_CurrentAnimationFrame{};
    float m_AnimTimer{ 0.f };
    bool m_LookingLeft{ false };

    bool m_IsHoldingLeft{};
    bool m_IsHoldingRight{};
    bool m_IsOnGround{};
};