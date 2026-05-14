#pragma once
#include "DecorInteractable.h"
#include <Vector2f.h>

class GunSmithNpcInteractable final : public DecorInteractable
{
  public:
    explicit GunSmithNpcInteractable(const Vector2f &cell);

    GunSmithNpcInteractable(const GunSmithNpcInteractable &) = delete;
    GunSmithNpcInteractable &operator=(const GunSmithNpcInteractable &) = delete;

    GunSmithNpcInteractable(GunSmithNpcInteractable &&) = delete;
    GunSmithNpcInteractable &operator=(GunSmithNpcInteractable &&) = delete;

    bool OnInteract(Game &game) override;
};
