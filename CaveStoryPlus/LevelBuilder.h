#pragma once
#include "Vector2f.h"

class Level;
class LevelBuilder
{
  public:
    Level *BuildCaveLevel();

    Vector2f GetSpawnPos() const;

  private:
    Vector2f m_SpawnPos;
};
