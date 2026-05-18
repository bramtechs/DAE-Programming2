#include "DoorInteractable.h"
#include "Game.h"
#include "Level.h"
#include "pch.h"
#include <cassert>

DoorInteractable::DoorInteractable(const Vector2f &cell, LevelBuilder::Type type, const Vector2f &customSpawn)
    : Interactable(cell), m_LevelType(type), m_CustomSpawn(customSpawn)
{
}

DoorInteractable::DoorInteractable(const Vector2f &cell, LevelBuilder::Type type)
    : Interactable(cell), m_LevelType(type), m_CustomSpawn()
{
}

void DoorInteractable::Update(float delta)
{
}

void DoorInteractable::Draw() const
{
}

bool DoorInteractable::OnInteract(Game &game)
{
    if (const Player * pPlayer{game.GetPlayer()})
    {
        Level *pLevel{LevelBuilder(*pPlayer).BuildLevel(m_LevelType)};
        game.SwitchLevel(pLevel);
        if (m_CustomSpawn.has_value())
        {
            pLevel->SetSpawnPos(m_CustomSpawn.value());
        }
    }

    return false;
}
