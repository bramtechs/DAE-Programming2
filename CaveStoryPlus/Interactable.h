#pragma once
#include "Vector2f.h"
#include "structs.h"

class Texture;
class Game;
class Player;
class Interactable
{
  public:
    explicit Interactable(const Rectf &region);
    explicit Interactable(const Vector2f &cell, const Vector2f &size = Vector2f{1.f, 1.f});
    explicit Interactable(const Vector2f &cell, const float size);
    virtual ~Interactable() = default;

    Interactable(const Interactable &) = default;
    Interactable &operator=(const Interactable &) = default;
    Interactable(Interactable &&) noexcept = default;
    Interactable &operator=(Interactable &&) noexcept = default;

    virtual void Update(float delta) = 0;
    virtual void Draw() const = 0;

    virtual bool IsExpired() const
    {
        return false;
    }

    // returns bool if consumed, should be destroyed
    virtual bool OnInteract(Game &game)
    {
        return false;
    }

    // returns bool if should be destroyed
    virtual bool OnTouch(Game &game)
    {
        return false;
    }

    void DrawDebug() const;

    void Translate(const Vector2f &offset);

    void SetSpriteSheetTexture(const Texture &texture);

    bool IsInside(const Player &player) const;
    Rectf GetRegion() const;
    Rectf GetTileRegion() const;
    Vector2f GetPosition() const;
    Vector2f GetCenter() const;

  protected:
    void SetRegion(const Rectf &region);

    const Texture &GetSpriteSheetTexture() const;

  private:
    Rectf m_Region{};
    const Texture *m_pSpriteSheetTexture{};
};
