#pragma once
#include "Interactable.h"

class LifeCapsule final : public Interactable
{
  public:
    LifeCapsule(const Vector2f &cell);

    void Update(float delta) override;
    void Draw() const override;

    void Interact(const GameContext &context) override;

  private:
    Rectf GetAnimationSource(int frame) const;

    float m_AnimTimer{};
    int m_FrameIndex{};
};
