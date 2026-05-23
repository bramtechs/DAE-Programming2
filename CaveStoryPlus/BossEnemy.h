#pragma once
#include "Enemy.h"

class BossEnemy final : public Enemy
{
  public:
    explicit BossEnemy(const Vector2f &pos);

    void Update(float delta) override;

    void Draw() const override;

  private:
    enum class State
    {
        talking,
        running,
        jumping,
        crushing
    };

    constexpr static int m_PixelsWidth{66};
    constexpr static int m_PixelsHeight{45};
    constexpr static float m_SecondsPerFrame{0.2f};

    void CalcSourceRect();

    Rectf m_SourceRect{};
    State m_State{State::talking};
    float m_AnimTimer{};
    int m_AnimFrame{};
};
