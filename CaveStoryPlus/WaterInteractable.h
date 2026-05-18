#pragma once
#include "Interactable.h"

class WaterInteractable final : public Interactable
{
  public:
    explicit WaterInteractable(const Rectf &region);

    void Update(float delta) override;
    void Draw() const override;

    bool OnTouch(Game &game);

  private:
    static constexpr float m_SecondsBetweenDrain{0.1f};
    float m_DrainTimer{};
};
