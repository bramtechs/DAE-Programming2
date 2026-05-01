#pragma once
#include "Interactable.h"

class LifeCapsuleInteractable final : public Interactable
{
  public:
    explicit LifeCapsuleInteractable(const Vector2f &cell);

    void Update(float delta) override;
    void Draw() const override;

    void Interact(Game &game) override;

  private:
    Rectf GetAnimationSource(int frame) const;

    float m_AnimTimer{};
    int m_FrameIndex{};
};
