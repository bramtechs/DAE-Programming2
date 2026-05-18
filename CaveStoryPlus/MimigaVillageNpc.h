#pragma once
#include "DecorInteractable.h"

class MimigaVillageNpc final : public DecorInteractable
{
  public:
    explicit MimigaVillageNpc(const Vector2f &cell);

    bool OnInteract(Game &game) override;

  private:
    static Rectf m_HidingSourceRegion;
    static Rectf m_TalkingSourceRegion;

    enum class State
    {
        hiding,
        talking,
        doneTalking
    };

    void StopHiding();

    State m_State{State::hiding};
};
