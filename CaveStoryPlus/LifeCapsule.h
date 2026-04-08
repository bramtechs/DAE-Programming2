#pragma once
#include "Interactable.h"

class LifeCapsule final : public Interactable
{
  public:
    LifeCapsule(const Vector2f &cell);

    void Interact(const GameContext &context) override;
};
