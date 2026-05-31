#pragma once
#include "Interactable.h"

class DecorInteractable : public Interactable
{
  public:
    virtual ~DecorInteractable() override = default;

    explicit DecorInteractable(const Rectf &region, const Rectf &sourceRect = {});
    explicit DecorInteractable(const Vector2f &cell, const Rectf &sourceRect = {});

    virtual void Update(float delta) override;
    virtual void Draw() const override;

    void SetSourceRect(const Rectf &region);

  private:
    Rectf m_SourceRect{};
};
