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

    // returns bool if consumed, should be destroyed
    virtual bool OnInteract(Game &game) = 0;

    // returns bool if consumed, should be destroyed
    virtual bool OnTouch(Game & /*game*/)
    {
        return false;
    }

    void DrawDebug() const;

    void Translate(const Vector2f &offset);

    Rectf GetRegion() const;

    Vector2f GetCenter() const;

  protected:
    const Texture &GetSpriteSheetTexture() const
    {
        return *m_pSpriteSheetTexture;
    }

    void SetRegion(const Rectf &region)
    {
        m_Region = region;
    }

  private:
    Rectf m_Region{};

    static Texture *m_pSpriteSheetTexture;
    static int m_InstanceCount;
};
