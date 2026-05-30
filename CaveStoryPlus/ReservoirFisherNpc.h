#pragma once
#include "DecorInteractable.h"

class ReservoirFisherNpc final : public DecorInteractable
{
  public:
    explicit ReservoirFisherNpc(const Vector2f &pos);

  private:
    static const Rectf m_SourceRect;
};
