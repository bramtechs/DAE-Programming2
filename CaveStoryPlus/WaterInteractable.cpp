#include "pch.h"
#include "WaterInteractable.h"
#include "Game.h"
#include "Player.h"

const float WaterInteractable::m_SecondsBetweenDrain{0.1f};

WaterInteractable::WaterInteractable(const Rectf &region) : Interactable(region)
{
}

void WaterInteractable::Update(float delta)
{
    m_DrainTimer += delta;
}

bool WaterInteractable::OnTouch(Game &game)
{
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
