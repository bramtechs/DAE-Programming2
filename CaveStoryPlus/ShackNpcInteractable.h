#pragma once
#include "DecorInteractable.h"

class ShackNpcInteractable final : public DecorInteractable
{
  public:
    explicit ShackNpcInteractable(const Vector2f &cell);

    bool OnInteract(Game &game) override;

  private:
    static Rectf m_HidingSourceRegion;
    static Rectf m_TalkingSourceRegion;
};
