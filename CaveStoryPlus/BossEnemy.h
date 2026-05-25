#pragma once
#include "Enemy.h"
#include <cstdint>

class Player;
class BossEnemy final : public Enemy
{
  public:
    explicit BossEnemy(const Vector2f &pos);

    void Update(float delta) override;

    void Draw() const override;

    void StartAttacking(Player &player);

  private:
    enum class State : std::uint8_t
    {
        talking,
        running,
        jumping,
        crushing
    };

    constexpr static int m_PixelsWidth{66};
    constexpr static int m_PixelsHeight{45};
    constexpr static float m_SecondsPerFrame{0.2f};

    void UpdateAnimations(float delta);

    void CalcSourceRect();

    Player *m_pPlayer{};
    Rectf m_SourceRect{};
    State m_State{State::talking};
    float m_AnimTimer{};
    int m_AnimFrame{};
};
