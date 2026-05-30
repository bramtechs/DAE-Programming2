#pragma once
#include "Interactable.h"
#include "LevelBuilder.h"

class Level;
class LevelBuilder;
class DoorInteractable final : public Interactable
{
  public:
    explicit DoorInteractable(const Vector2f &cell, LevelBuilder::Type type, const Vector2f &customSpawn);
    explicit DoorInteractable(const Vector2f &cell, LevelBuilder::Type type);

    void Update(float delta) override;

    void Draw() const override;

    bool OnInteract(Game &game) override;

  private:
    const LevelBuilder::Type m_LevelType;
    const Vector2f m_CustomSpawn;
    const bool m_HasCustomSpawn;
};
