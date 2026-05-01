#pragma once
#include "Vector2f.h"
#include "structs.h"

class Texture;
class Game;
class Player;
class Interactable
{
  public:
    explicit Interactable(const Vector2f &cell, const Vector2f &size = Vector2f{1.f, 1.f});
    explicit Interactable(const Vector2f &cell, const float size);
    virtual ~Interactable();

    bool IsInside(const Player &player) const;

    virtual void Update(float delta) = 0;
    virtual void Draw() const = 0;
    virtual bool Interact(Game &game) = 0;

    void DrawDebug() const;

    Rectf GetRegion() const
    {
        return m_Region;
    }

  protected:
    const Texture &GetSpriteSheetTexture() const
    {
        return *m_pSpriteSheetTexture;
    }

  private:
    Rectf m_Region{};

    static Texture *m_pSpriteSheetTexture;
    static int m_InstanceCount;
};
