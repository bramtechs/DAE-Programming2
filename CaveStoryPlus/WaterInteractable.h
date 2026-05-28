#pragma once
#include "Interactable.h"

class WaterInteractable final : public Interactable
{
  public:
    explicit WaterInteractable(const Rectf &region);

    void Update(float delta) override;
    void Draw() const override;

    bool OnTouch(Game &game) override;

  private:
    static const float m_SecondsBetweenDrain;
    float m_DrainTimer{};
};
