#pragma once
#include "Interactable.h"

class LifeCapsuleInteractable final : public Interactable
{
  public:
    explicit LifeCapsuleInteractable(const Vector2f &cell);

    void Update(float delta) override;
    void Draw() const override;

    bool OnInteract(Game &game) override;

  private:
    Rectf GetAnimationSource(int frame) const;

    static void GiveExtraMaxHealth(Game &game);

    float m_AnimTimer{};
    int m_FrameIndex{};
};
