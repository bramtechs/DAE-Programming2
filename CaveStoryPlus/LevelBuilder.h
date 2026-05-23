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
        mimigaReservoir,
        mimigaShack,
    };

    explicit LevelBuilder(const Player &player);

    Level *BuildLevel(Type type) const;

  private:
    Level *BuildCaveLevel() const;
    Level *BuildHermitGunsmithLevel() const;
    Level *BuildMimigaVillageLevel() const;
    Level *BuildMimigaReservoirLevel() const;
    Level *BuildMimigaShackLevel() const;

    const Player &m_Player;
};
