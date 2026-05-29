#pragma once

class Player;
class Level;
class Game;

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

    explicit LevelBuilder(const Player &player, const Game& game);

    Level *BuildLevel(Type type) const;

  private:
    Level *BuildCaveLevel() const;
    Level *BuildHermitGunsmithLevel() const;
    Level *BuildMimigaVillageLevel() const;
    Level *BuildMimigaReservoirLevel() const;
    Level *BuildMimigaShackLevel() const;

    const Player &m_Player;
    const Game &m_Game;
};
