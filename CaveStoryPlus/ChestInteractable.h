#pragma once
#include "Interactable.h"

class ChestInteractable final : public Interactable
{
  public:
    explicit ChestInteractable(const Vector2f &cell);

    void Update(float delta) override;
    void Draw() const override;

  private:
    bool OnInteract(Game &game) override;

    bool m_IsOpened{};

    static const Rectf s_ClosedSourceRect;
    static const Rectf s_OpenSourceRect;
};
