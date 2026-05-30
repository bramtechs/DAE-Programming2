#include "pch.h"
#include "SoundManager.h"

SoundManager::SoundManager()
    : m_ChestOpenSfx("chest_open.wav"), m_DoorSfx("door.wav"), m_SplashSfx("splash.wav"),
      m_PlayerHurtSfx("player_hurt.wav"), m_PlayerJumpSfx("player_jump.wav"), m_CritterJumpSfx("critter_jump.wav"),
      m_GetItemSfx("get_item.wav"), m_GoldPickupSfx("gold_pickup.wav"), m_EnemyHurtSfx("enemy_hurt.wav"),
      m_LevelupSfx("level_up.wav"), m_PolarStarShootSfx("polar_star_shoot.wav"), m_HealthRefillSfx("health_refill.wav"),
      m_WalkSfx("walk.wav")
{
}

void SoundManager::PlaySound(Effect effect, int loops) const
{
    switch (effect)
    {
    case Effect::chest_open:
        m_ChestOpenSfx.Play(loops);
        break;
    case Effect::splash:
        m_SplashSfx.Play(loops);
        break;
    case Effect::player_hurt:
        m_PlayerHurtSfx.Play(loops);
        break;
    case Effect::player_jump:
        m_PlayerJumpSfx.Play(loops);
        break;
    case Effect::get_item:
        m_GetItemSfx.Play(loops);
        break;
    case Effect::gold_pickup:
        m_GoldPickupSfx.Play(loops);
        break;
    case Effect::critter_jump:
        m_CritterJumpSfx.Play(loops);
        break;
    case Effect::health_refill:
        m_HealthRefillSfx.Play(loops);
        break;
    case Effect::door:
        m_DoorSfx.Play(loops);
        break;
    case Effect::enemy_hurt:
        m_EnemyHurtSfx.Play(loops);
        break;
    case Effect::level_up:
        m_LevelupSfx.Play(loops);
        break;
    case Effect::polar_star_shoot:
        m_PolarStarShootSfx.Play(loops);
        break;
    case Effect::walk:
        m_WalkSfx.Play(loops);
        break;
    }
}
