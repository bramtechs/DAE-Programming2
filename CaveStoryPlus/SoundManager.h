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
    ~SoundManager();

    SoundManager(const SoundManager &) = delete;
    SoundManager &operator=(const SoundManager &) = delete;

    SoundManager(SoundManager &&) = delete;
    SoundManager &operator=(SoundManager &&) = delete;

    void PlaySound(Effect effect, int loops = 0) const;

  private:
    const SoundEffect *m_pChestOpenSfx;
    const SoundEffect *m_pDoorSfx;
    const SoundEffect *m_pSplashSfx;
    const SoundEffect *m_pPlayerHurtSfx;
    const SoundEffect *m_pPlayerJumpSfx;
    const SoundEffect *m_pCritterJumpSfx;
    const SoundEffect *m_pGetItemSfx;
    const SoundEffect *m_pGoldPickupSfx;
    const SoundEffect *m_pEnemyHurtSfx;
    const SoundEffect *m_pLevelupSfx;
    const SoundEffect *m_pPolarStarShootSfx;
    const SoundEffect *m_pHealthRefillSfx;
    const SoundEffect *m_pWalkSfx;
};
