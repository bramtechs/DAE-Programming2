#pragma once
#include "Interactable.h"

class DecorInteractable : public Interactable
{
  public:
    explicit DecorInteractable(const Rectf &region, const Rectf &sourceRect = {});
    explicit DecorInteractable(const Vector2f &cell, const Rectf &sourceRect = {});

    DecorInteractable(const DecorInteractable &) = delete;
    DecorInteractable &operator=(const DecorInteractable &) = delete;

    DecorInteractable(DecorInteractable &&) = delete;
    DecorInteractable &operator=(DecorInteractable &&) = delete;

    void Update(float delta) override;
    void Draw() const override;

    void SetSourceRect(const Rectf &region);

  private:
    Rectf m_SourceRect{};
};
