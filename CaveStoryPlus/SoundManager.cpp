#include "pch.h"
#include "SoundManager.h"
#include "SoundEffect.h"

SoundManager::SoundManager()
    : m_pChestOpenSfx(new SoundEffect("chest_open.wav")), m_pDoorSfx(new SoundEffect("door.wav")),
      m_pSplashSfx(new SoundEffect("splash.wav")), m_pPlayerHurtSfx(new SoundEffect("player_hurt.wav")),
      m_pPlayerJumpSfx(new SoundEffect("player_jump.wav")), m_pCritterJumpSfx(new SoundEffect("critter_jump.wav")),
      m_pGetItemSfx(new SoundEffect("get_item.wav")), m_pGoldPickupSfx(new SoundEffect("gold_pickup.wav")),
      m_pEnemyHurtSfx(new SoundEffect("enemy_hurt.wav")), m_pLevelupSfx(new SoundEffect("level_up.wav")),
      m_pPolarStarShootSfx(new SoundEffect("polar_star_shoot.wav")),
      m_pHealthRefillSfx(new SoundEffect("health_refill.wav")), m_pWalkSfx(new SoundEffect("walk.wav"))
{
}

SoundManager::~SoundManager()
{
    delete m_pChestOpenSfx;
    delete m_pDoorSfx;
    delete m_pSplashSfx;
    delete m_pPlayerHurtSfx;
    delete m_pPlayerJumpSfx;
    delete m_pCritterJumpSfx;
    delete m_pGetItemSfx;
    delete m_pGoldPickupSfx;
    delete m_pEnemyHurtSfx;
    delete m_pLevelupSfx;
    delete m_pPolarStarShootSfx;
    delete m_pHealthRefillSfx;
    delete m_pWalkSfx;
}

void SoundManager::PlaySound(Effect effect, int loops) const
{
    switch (effect)
    {
    case Effect::chest_open:
        m_pChestOpenSfx->Play(loops);
        break;
    case Effect::splash:
        m_pSplashSfx->Play(loops);
        break;
    case Effect::player_hurt:
        m_pPlayerHurtSfx->Play(loops);
        break;
    case Effect::player_jump:
        m_pPlayerJumpSfx->Play(loops);
        break;
    case Effect::get_item:
        m_pGetItemSfx->Play(loops);
        break;
    case Effect::gold_pickup:
        m_pGoldPickupSfx->Play(loops);
        break;
    case Effect::critter_jump:
        m_pCritterJumpSfx->Play(loops);
        break;
    case Effect::health_refill:
        m_pHealthRefillSfx->Play(loops);
        break;
    case Effect::door:
        m_pDoorSfx->Play(loops);
        break;
    case Effect::enemy_hurt:
        m_pEnemyHurtSfx->Play(loops);
        break;
    case Effect::level_up:
        m_pLevelupSfx->Play(loops);
        break;
    case Effect::polar_star_shoot:
        m_pPolarStarShootSfx->Play(loops);
        break;
    case Effect::walk:
        m_pWalkSfx->Play(loops);
        break;
    }
}
