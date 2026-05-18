#pragma once
#include "Interactable.h"
#include <functional>
#include <optional>

class Level;
class LevelBuilder;
class DoorInteractable final : public Interactable
{
  public:
    using LevelBuilder = std::function<Level *()>;

    explicit DoorInteractable(const Vector2f &cell, const LevelBuilder &levelBuilder);
    explicit DoorInteractable(const Vector2f &cell, const LevelBuilder &levelBuilder, Vector2f customSpawn);

    void Update(float delta) override;

    void Draw() const override;

    bool OnInteract(Game &game) override;

  private:
    const LevelBuilder m_LevelBuilderFunc;
    const std::optional<Vector2f> m_CustomSpawn;
};
