#pragma once
#include "Interactable.h"
#include "structs.h"

class Level;
class GoldInteractable final : public Interactable
{
  public:
    explicit GoldInteractable(const Vector2f &cell, Level &level);

    // returns true if expired
    void Update(float delta) override;

    void Draw() const override;

    // returns bool if should be destroyed
    bool OnTouch(Game &game) override;

  private:
    Rectf GetAnimationFrameSource() const;
    Circlef GetHitbox() const;

    constexpr static float m_TimePerFrame{0.1f};
    constexpr static float m_Gravity{-9.81f};

    Level &m_Level;
    Vector2f m_Velocity{};
    float m_AnimTimer{};
    int m_AnimFrame{};
};
