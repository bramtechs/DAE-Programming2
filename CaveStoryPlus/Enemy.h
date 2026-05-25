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

    virtual bool IsSolid() const
    {
        return false;
    }

    virtual int GetGoldDropCount() const
    {
        return 1;
    }

    // returns true if died
    bool TakeDamage(int damage);

    void SetCenter(Vector2f position);
    Vector2f GetCenter() const;

    Rectf GetRegion() const;
    Circlef GetCircleRegion() const;

  protected:
    void SetHealth(int health)
    {
        m_Health = health;
    }

    void Translate(const Vector2f &offset)
    {
        m_Position += offset;
    }

    void SetPosition(const Vector2f &pos)
    {
        m_Position = pos;
    }

    const Vector2f &GetPosition() const
    {
        return m_Position;
    }

    const Texture &GetSpriteSheet() const
    {
        return *m_pSpriteSheetTexture;
    }

  private:
    void DealBodyDamage(Player &player);

    Vector2f m_Position{};
    Vector2f m_Size{};
    int m_Health{3};
    int m_BodyDamage{1};

    static Texture *m_pSpriteSheetTexture;
    static int m_InstanceCount;
};
