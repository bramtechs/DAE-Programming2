#pragma once
#include "Enemy.h"
#include "BarWidget.h"
#include <cstdint>

class Game;
class Player;
class BossEnemy final : public Enemy
{
  public:
    explicit BossEnemy(const Vector2f &pos, float areaLeft, float areaRight);

    void Update(float delta) override;

    void Draw() const override;

    void DrawGUI(const Rectf &viewport) const override;

    void StartAttacking(Player &player, Game &game);

    int GetGoldDropCount() const override
    {
        return 5;
    }

  private:
    enum class State
    {
        talking,
        moving,
        crushing,
        fleeing,
        done
    };

    static const int m_PixelsWidth;
    static const int m_PixelsHeight;
    static const float m_SecondsPerFrame;
    static const float m_MovementAccel;
    static const float m_SecondsBetweenJumps;
    static const float m_SecondsCrushing;
    static const float m_JumpForce;
    static const Rectf m_BossLabelSourceRect;

    bool TakeDamage(int amount) override;

    void UpdateAnimations(float delta);

    void CalcSourceRect(bool isJumping);

    Player *m_pPlayer{};
    Game *m_pGame{};
    Rectf m_SourceRect{};
    State m_State{State::talking};
    Vector2f m_Velocity{};
    BarWidget m_BarWidget{Color4f{37.f / 255.f, 44.f / 255.f, 63.f / 255.f, 1.f},
                          Color4f{255.f / 255.f, 2.f / 255.f, 3.f / 255.f, 1.f}};
    const float m_AreaLeft{};
    const float m_AreaRight{};
    const float m_FloorTop{};
    const int m_MaxHealth{15};
    float m_AnimTimer{};
    float m_JumpTimer{};
    float m_CrushingTimer{};
    int m_AnimFrame{};
};
