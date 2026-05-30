#pragma once
#include "DecorInteractable.h"

class Game;
class ReservoirSignInteractable final : public DecorInteractable
{
  public:
    explicit ReservoirSignInteractable(const Vector2f &tile);

    bool OnInteract(Game &game) override;

  private:
    static const Rectf m_TextureSourceRect;
};
