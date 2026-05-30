#pragma once
#include "Interactable.h"
#include "Vector2f.h"
#include "structs.h"

class SpikeInteractable final : public Interactable
{
  public:
    enum class Orientation
    {
        floor,
        ceiling,
        leftWall,
        rightWall
    };

    explicit SpikeInteractable(const Vector2f &cell, Orientation orientation = Orientation::floor);

    void Update(float delta) override;

    void Draw() const override;

    bool OnTouch(Game &game) override;

  private:
    Rectf GetSourceRegion() const;

    const Orientation m_Orientation{};
};
