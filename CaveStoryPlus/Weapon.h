#pragma once
#include "structs.h"

class Weapon
{
  public:
    enum class Orientation
    {
        north = -90,
        east = 0,
        south = 90,
        west = 180
    };

    virtual ~Weapon() = default;

    virtual void Shoot(const Vector2f &handPos, Orientation orientation) = 0;
    virtual void Draw(const Vector2f &handPos, Orientation orientation) const = 0;
};