#include "pch.h"
#include "SoundManager.h"

SoundManager::SoundManager()
    : m_ChestOpenSfx("chestopen.wav"), m_DoorSfx("door.wav"), m_EnemyHurtSfx("enemy_hurt.wav"),
      m_LevelupSfx("levelup.wav"), m_PolarStarShootSfx("polar_star_shoot.wav"), m_WalkSfx("walk.wav")
{
}

void SoundManager::PlaySound(Effect effect, int loops) const
{
    switch (effect)
    {
    case Effect::chestopen:
        m_ChestOpenSfx.Play(loops);
        break;
    case Effect::door:
        m_DoorSfx.Play(loops);
        break;
    case Effect::enemy_hurt:
        m_EnemyHurtSfx.Play(loops);
        break;
    case Effect::levelup:
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
