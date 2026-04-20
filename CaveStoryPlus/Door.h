#pragma once
#include "Interactable.h"
#include <functional>

class Level;
class LevelBuilder;
class Door final : public Interactable
{
  public:
    explicit Door(const Vector2f &cell, const std::function<Level *()> &levelBuilder);

    void Update(float delta) override;

    void Draw() const override;

    void Interact(Game &game) override;

  private:
    const std::function<Level *()> m_LevelBuilderFunc;
};
