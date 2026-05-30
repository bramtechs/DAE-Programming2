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
    const SoundEffect m_ChestOpenSfx;
    const SoundEffect m_DoorSfx;
    const SoundEffect m_EnemyHurtSfx;
    const SoundEffect m_LevelupSfx;
    const SoundEffect m_PolarStarShootSfx;
    const SoundEffect m_WalkSfx;
};
