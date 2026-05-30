#pragma once
#include "SoundEffect.h"

class SoundManager final
{
  public:
    enum class Effect
    {
        chest_open,
        door,
        splash,
        player_hurt,
        enemy_hurt,
        player_jump,
        critter_jump,
        get_item,
        gold_pickup,
        level_up,
        polar_star_shoot,
        health_refill,
        walk
    };

    SoundManager();

    void PlaySound(Effect effect, int loops = 0) const;

  private:
    const SoundEffect m_ChestOpenSfx;
    const SoundEffect m_DoorSfx;
    const SoundEffect m_SplashSfx;
    const SoundEffect m_PlayerHurtSfx;
    const SoundEffect m_PlayerJumpSfx;
    const SoundEffect m_CritterJumpSfx;
    const SoundEffect m_GetItemSfx;
    const SoundEffect m_GoldPickupSfx;
    const SoundEffect m_EnemyHurtSfx;
    const SoundEffect m_LevelupSfx;
    const SoundEffect m_PolarStarShootSfx;
    const SoundEffect m_HealthRefillSfx;
    const SoundEffect m_WalkSfx;
};
