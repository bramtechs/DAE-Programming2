#pragma once
#include "Vector2f.h"
#include "structs.h"

class Texture;
class Game;
class Player;
class Interactable
{
  public:
    Interactable(const Vector2f &cell);
    virtual ~Interactable();

    bool IsInside(const Player &player) const;

    virtual void Update(float delta) = 0;
    virtual void Draw() const = 0;
    virtual void Interact(Game &game) = 0;

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
