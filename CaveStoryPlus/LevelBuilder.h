#pragma once
#include "Vector2f.h"

class Level;
class LevelBuilder
{
  public:
    static Level *BuildCaveLevel();

    static Level *BuildHermitGunsmithLevel();
};
