#pragma once
#include "Interactable.h"
#include "structs.h"

class GoldInteractable final : public Interactable
{
  public:
    explicit GoldInteractable(const Vector2f &cell);

    void Update(float delta) override;

    void Draw() const override;

    bool Interact(Game &game) override;

  private:
    Rectf GetAnimationFrameSource() const;

    constexpr static float s_TimePerFrame{0.1f};

    float m_AnimTimer{};
    int m_AnimFrame{};
};
