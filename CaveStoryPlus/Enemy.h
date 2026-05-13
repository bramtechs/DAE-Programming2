#pragma once
#include "structs.h"

class Player;
class Texture;
class Enemy
{
  public:
    Enemy(const Vector2f &size);

    virtual ~Enemy();

    virtual void InteractWithPlayer(Player &player) = 0;

    virtual void Update(float delta) = 0;

    virtual void Draw() const = 0;

    virtual void DrawDebug() const;

    // returns true if died
    bool TakeDamage(int damage);

    void SetCenter(Vector2f position);
    Vector2f GetPosition() const;

    Rectf GetRegion() const;

  protected:
    const Texture &GetSpriteSheet() const
    {
        return *m_pSpriteSheetTexture;
    }

    Vector2f m_Position{};
    Vector2f m_Size{};
    int m_Health{};

  private:
    static Texture *m_pSpriteSheetTexture;
    static int m_InstanceCount;
};
