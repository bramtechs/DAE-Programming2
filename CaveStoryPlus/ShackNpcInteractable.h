#pragma once
#include "DecorInteractable.h"
#include "DialogEvent.h"

class BossEnemy;
class DialogManager;
class ShackNpcInteractable final : public DecorInteractable
{
  public:
    explicit ShackNpcInteractable(const Vector2f &cell);

    void Update(float delta) override;

    bool OnInteract(Game &game) override;

  private:
    class StartTalkingDialogEvent final : public DialogEvent
    {
      public:
        explicit StartTalkingDialogEvent(ShackNpcInteractable &npc);

        void Execute(Game &game) override;

      private:
        ShackNpcInteractable &m_Npc;
    };

    class SpawnBossEnemyDialogEvent final : public DialogEvent
    {
      public:
        explicit SpawnBossEnemyDialogEvent(ShackNpcInteractable &npc);

        void Execute(Game &game) override;

      private:
        ShackNpcInteractable &m_Npc;
    };

    static const Rectf m_HidingSourceRegion;
    static const Rectf m_TalkingSourceRegion;

    DialogManager *m_pDialogManager{};
    bool m_DoneTalking{};
};
