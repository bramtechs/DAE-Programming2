#pragma once
#include "Interactable.h"

class HeartInteractable final : public Interactable
{
  public:
    explicit HeartInteractable(const Vector2f &cell);

    void Update(float delta) override;

    void Draw() const override;

    bool OnTouch(Game &game) override;

    bool IsExpired() const;

  private:
    Rectf GetAnimationFrameSource(bool flashed) const;

    float m_Timer{};
    float m_FlashInterval{2.5f};
};
