#pragma once

class Player;
class Level;

class LevelBuilder
{
  public:
    enum class Type
    {
        cave,
        hermitGunsmith,
        mimigaVillage,
        mimigaReservoir
    };

    explicit LevelBuilder(const Player &player);

    Level *BuildLevel(Type type) const;

  private:
    Level *BuildCaveLevel() const;
    Level *BuildHermitGunsmithLevel() const;
    Level *BuildMimigaVillageLevel() const;
    Level *BuildReservoirLevel() const;

    const Player &m_Player;
};
