#pragma once
#include "DecorInteractable.h"
#include "DialogEvent.h"

class MimigaVillageNpc final : public DecorInteractable
{
  public:
    explicit MimigaVillageNpc(const Vector2f &cell);

    bool OnInteract(Game &game) override;

    class StopHidingDialogEvent final : public DialogEvent
    {
      public:
        explicit StopHidingDialogEvent(MimigaVillageNpc &npc);

        void Execute(Game &game) override;

      private:
        MimigaVillageNpc &m_Npc;
    };

    class DoneTalkingDialogEvent final : public DialogEvent
    {
      public:
        explicit DoneTalkingDialogEvent(MimigaVillageNpc &npc);

        void Execute(Game &game) override;

      private:
        MimigaVillageNpc &m_Npc;
    };

  private:
    static Rectf m_HidingSourceRegion;
    static Rectf m_TalkingSourceRegion;

    enum class State
    {
        hiding,
        talking,
        doneTalking
    };

    State m_State{State::hiding};
};
