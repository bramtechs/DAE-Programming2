#pragma once
#include "SoundEffect.h"

class SoundManager
{
  public:
    enum class Effect
    {
        chestopen,
        door,
        enemy_hurt,
        levelup,
        polar_star_shoot,
        walk
    };

    SoundManager();

    void PlaySound(Effect effect, int loops = 0) const;

  private:
    SoundEffect m_ChestOpenSfx;
    SoundEffect m_DoorSfx;
    SoundEffect m_EnemyHurtSfx;
    SoundEffect m_LevelupSfx;
    SoundEffect m_PolarStarShootSfx;
    SoundEffect m_WalkSfx;
};
