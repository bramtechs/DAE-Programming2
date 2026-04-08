#pragma once
#include "Vector2f.h"
#include "structs.h"

class GameContext;
class Player;
class Interactable
{
  public:
    Interactable(const Vector2f &cell);
    virtual ~Interactable() = default;

    bool IsInside(const Player &player) const;

    void DrawDebug() const;

    virtual void Interact(const GameContext &context) = 0;

  private:
    Rectf m_Region{};
};
