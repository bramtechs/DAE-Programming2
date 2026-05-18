#pragma once
#include "Interactable.h"
#include "LevelBuilder.h"
#include <functional>
#include <optional>

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
    LevelBuilder::Type m_LevelType;
    std::optional<Vector2f> m_CustomSpawn;
};
