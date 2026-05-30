#include "DoorInteractable.h"
#include "SoundManager.h"
#include "Game.h"
#include "Level.h"
#include "pch.h"
#include <cassert>

DoorInteractable::DoorInteractable(const Vector2f &cell, LevelBuilder::Type type, const Vector2f &customSpawn)
    : Interactable(cell), m_LevelType(type), m_CustomSpawn(customSpawn), m_HasCustomSpawn(true)
{
}

DoorInteractable::DoorInteractable(const Vector2f &cell, LevelBuilder::Type type)
    : Interactable(cell), m_LevelType(type), m_CustomSpawn(), m_HasCustomSpawn(false)
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
    const Player *pPlayer{game.GetPlayer()};
    if (pPlayer)
    {
        game.GetSoundManager()->PlaySound(SoundManager::Effect::door);
        Level *pLevel{LevelBuilder(*pPlayer, game).BuildLevel(m_LevelType)};
        game.SwitchLevel(pLevel);

        if (m_HasCustomSpawn)
        {
            pLevel->SetSpawnPos(m_CustomSpawn);
        }
    }

    return false;
}
