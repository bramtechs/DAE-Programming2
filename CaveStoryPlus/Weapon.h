#pragma once
#include "structs.h"

class BulletManager;
class Weapon
{
  public:
    enum class Orientation
    {
        north = 90,
        east = 0,
        west = 180,
        south = 270,
    };

    virtual ~Weapon() = default;

    virtual void Shoot(const Vector2f &handPos, Orientation orientation, BulletManager &manager) = 0;
    virtual void Draw(const Vector2f &handPos, Orientation orientation) const = 0;
};
