#pragma once
#include "Interactable.h"
#include <functional>

class Level;
class LevelBuilder;
class DoorInteractable final : public Interactable
{
  public:
    explicit DoorInteractable(const Vector2f &cell, const std::function<Level *()> &levelBuilder);

    void Update(float delta) override;

    void Draw() const override;

    bool Interact(Game &game) override;

  private:
    const std::function<Level *()> m_LevelBuilderFunc;
};
