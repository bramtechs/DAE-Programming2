#pragma once
#include "structs.h"

class Player;
class SoundManager;
class Texture;
class Enemy
{
  public:
    explicit Enemy(const Vector2f &size);
    virtual ~Enemy() = default;

    Enemy(const Enemy &) = default;
    Enemy &operator=(const Enemy &) = default;
    Enemy(Enemy &&) noexcept = default;
    Enemy &operator=(Enemy &&) noexcept = default;

    virtual void InteractWithPlayer(Player &player);

    virtual void Update(float delta) = 0;

    virtual void Draw() const = 0;

    virtual void DrawGUI(const Rectf &viewport) const
    {
    }

    virtual void DrawDebug() const;

    virtual bool IsSolid() const
    {
        return false;
    }

    virtual int GetGoldDropCount() const
    {
        return 1;
    }

    void SetSpriteSheetTexture(const Texture &texture);
    void SetSoundManager(const SoundManager *pSoundManager);

    // returns true if died
    virtual bool TakeDamage(int damage);

    int GetHealth() const;

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
    const Vector2f m_Size{};
    const Texture *m_pSpriteSheetTexture{};
    const SoundManager *m_pSoundManager{};
    int m_Health{3};
    int m_BodyDamage{1};
};
