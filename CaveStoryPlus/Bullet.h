#pragma once
#include "Vector2f.h"
#include "structs.h"

class Enemy;
class Texture;
class Bullet
{
  public:
    explicit Bullet(const Vector2f &position);
    Bullet() = default;

    void Update(float delta);
    void Draw(const Texture &texture) const;

    void SetVelocity(const Vector2f &velocity);
    void SetVelocityFromAngle(float angleRadians, float speed);

    void SetDamage(int damage);
    void SetSourceRegion(const Rectf &region);

    void SetScale(float scale);

    Rectf GetRegion() const;
    Circlef GetCircleRegion() const;

    bool IsOverlapping(const Rectf &region) const;

    int GetDamage() const;

  private:
    float GetAngleDegrees() const;

    Vector2f m_Position{};
    Vector2f m_Velocity{};
    Rectf m_SourceRegion{};
    float m_Scale{1.f};
    int m_Damage{1};
};
