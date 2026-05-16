#pragma once
#include "structs.h"

class Player;
class Texture;
class Enemy
{
  public:
    Enemy(const Vector2f &size);
    virtual ~Enemy();
    Enemy(const Enemy &) = delete;
    Enemy &operator=(const Enemy &) = delete;
    Enemy(Enemy &&) = delete;
    Enemy &operator=(Enemy &&) = delete;

    virtual void InteractWithPlayer(Player &player);

    virtual void Update(float delta) = 0;

    virtual void Draw() const = 0;

    virtual void DrawDebug() const;

    // returns true if died
    bool TakeDamage(int damage);

    void SetCenter(Vector2f position);
    Vector2f GetCenter() const;

    Rectf GetRegion() const;
    Circlef GetCircleRegion() const;

  protected:
    const Texture &GetSpriteSheet() const
    {
        return *m_pSpriteSheetTexture;
    }

    Vector2f m_Position{};
    Vector2f m_Size{};
    int m_Health{};
    int m_BodyDamage{1};

  private:
    void DealBodyDamage(Player &player);

    static Texture *m_pSpriteSheetTexture;
    static int m_InstanceCount;
};
