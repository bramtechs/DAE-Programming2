#pragma once
#include "Interactable.h"
#include "DialogEvent.h"

class LifeCapsuleInteractable final : public Interactable
{
  public:
    explicit LifeCapsuleInteractable(const Vector2f &cell);

    void Update(float delta) override;
    void Draw() const override;

    bool OnInteract(Game &game) override;

  private:
    class GiveMaxHealthDialogEvent final : public DialogEvent
    {
      public:
        explicit GiveMaxHealthDialogEvent(int amount);

        void Execute(Game &game) override;

      private:
        int m_Amount;
    };

    Rectf GetAnimationSource(int frame) const;

    float m_AnimTimer{};
    int m_FrameIndex{};
};
