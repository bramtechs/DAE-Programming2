#include "pch.h"
#include "WaterInteractable.h"
#include "SoundManager.h"
#include "Game.h"
#include "Player.h"

const float WaterInteractable::m_SecondsBetweenDrain{0.1f};

WaterInteractable::WaterInteractable(const Rectf &region, const SoundManager& soundManager) 
    : Interactable(region), m_SoundManager(soundManager)
{
}

void WaterInteractable::Update(float delta)
{
    m_DrainTimer += delta;
    m_SplashSoundTimer += delta;
}

bool WaterInteractable::OnTouch(Game &game)
{
    if (m_SplashSoundTimer > 3.f)
    {
        m_SoundManager.PlaySound(SoundManager::Effect::splash);
        m_SplashSoundTimer = 0.f;
    }

    if (m_DrainTimer > m_SecondsBetweenDrain)
    {
        game.GetPlayer()->DrainOxygen();
        m_DrainTimer = 0.f;
    }
    return false;
}

void WaterInteractable::Draw() const
{
}
