#pragma once
#include "Interactable.h"

class PickupInteractable final : public Interactable
{
  public:
    explicit PickupInteractable(const Vector2f &cell);

    void Update(float delta) override;
    void Draw() const override;

    bool OnInteract(Game &game);

  private:
    static constexpr float m_TimePerFrame{0.2f};
    static Rectf GetAnimationFrameSource(int frame);

    int m_CurrentFrame{};
    float m_AnimationTimer{};
};
