#pragma once
#include "Enemy.h"

class Level;
class PolygonCollider;
class JumperEnemy final : public Enemy
{
  public:
    explicit JumperEnemy(const Vector2f &pos, Level &level);

    void InteractWithPlayer(Player &player) override;

    void Update(float delta) override;

    void Draw() const override;

    void DrawDebug() const override;

    int GetGoldDropCount() const override
    {
        return 2;
    }

  private:
    enum class State
    {
        idle,
        charging,
        jumping
    };

    Vector2f m_Velocity{};
    Vector2f m_LastPosition{};
    State m_State{};
    float m_ChargeTimer{};
    bool m_IsLookingRight{};
    Level &m_Level;

    bool IsOverlappingLevel(PolygonCollider &outShape) const;

    Rectf GetSourceRect() const;

    static constexpr float m_Gravity{9.81f};
    static constexpr float m_JumpForce{8.f};
    static constexpr float m_ChargeRange{3.f};
    static constexpr float m_ChargeTime{2.f};
    static const Rectf m_ChargingSourceRect;
    static const Rectf m_IdleSourceRect;
    static const Rectf m_JumpingSourceRect;
};
