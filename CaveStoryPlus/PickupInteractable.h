#pragma once
#include "Interactable.h"

class SoundManager;
class PickupInteractable final : public Interactable
{
  public:
    explicit PickupInteractable(const Vector2f &cell);

    void Update(float delta) override;
    void Draw() const override;

    bool OnInteract(Game &game) override;

  private:
    static Rectf GetAnimationFrameSource(int frame);

    static const float m_TimePerFrame;

    int m_CurrentFrame{};
    float m_AnimationTimer{};
};
