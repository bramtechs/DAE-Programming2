#pragma once
#include "Enemy.h"

class JumperEnemy final : public Enemy
{
  public:
    explicit JumperEnemy(const Vector2f &pos);

    void InteractWithPlayer(Player &player) override;

    void Update(float delta) override;

    void Draw() const override;

    void DrawDebug() const override;

  private:
    enum class State
    {
        idle,
        charging,
        jumping
    };

    Vector2f m_Velocity{};
    State m_State{};
    float m_ChargeTimer{};
    bool m_IsLookingRight{};

    Rectf GetSourceRect() const;

    static constexpr float m_Gravity{9.81f};
    static constexpr float m_JumpForce{8.f};
    static constexpr float m_ChargeRange{3.f};
    static constexpr float m_ChargeTime{2.f};
    static const Rectf m_ChargingSourceRect;
    static const Rectf m_IdleSourceRect;
    static const Rectf m_JumpingSourceRect;
};
