#pragma once
#include "Interactable.h"

class SoundManager;
class WaterInteractable final : public Interactable
{
  public:
    explicit WaterInteractable(const Rectf &region, const SoundManager &soundManager);

    void Update(float delta) override;
    void Draw() const override;

    bool OnTouch(Game &game) override;

  private:
    static const float m_SecondsBetweenDrain;
    const SoundManager &m_SoundManager;
    float m_DrainTimer{};
    float m_SplashSoundTimer{};
};
