#pragma once
#include "Enemy.h"
#include <cstdint>

class Player;
class BossEnemy final : public Enemy
{
  public:
    explicit BossEnemy(const Vector2f &pos, float areaLeft, float areaRight);

    void Update(float delta) override;

    void Draw() const override;

    void StartAttacking(Player &player);

  private:
    enum class State : std::uint8_t
    {
        talking,
        moving,
        crushing
    };

    constexpr static int m_PixelsWidth{66};
    constexpr static int m_PixelsHeight{45};
    constexpr static float m_SecondsPerFrame{0.2f};
    constexpr static float m_MovementAccel{1.35f};
    constexpr static float m_SecondsBetweenJumps{3.f};
    constexpr static float m_SecondsCrushing{2.f};
    constexpr static float m_JumpForce{5.f};

    void UpdateAnimations(float delta);

    void CalcSourceRect(bool isJumping);

    Player *m_pPlayer{};
    Rectf m_SourceRect{};
    State m_State{State::talking};
    Vector2f m_Velocity{};
    float m_AreaLeft{};
    float m_AreaRight{};
    float m_FloorTop{};
    float m_AnimTimer{};
    float m_JumpTimer{};
    float m_CrushingTimer{};
    int m_AnimFrame{};
};
