#pragma once
#include "DecorInteractable.h"
#include <Vector2f.h>

class GunSmithNpcInteractable final : public DecorInteractable
{
  public:
    explicit GunSmithNpcInteractable(const Vector2f &cell);

    bool OnInteract(Game &game) override;
};
