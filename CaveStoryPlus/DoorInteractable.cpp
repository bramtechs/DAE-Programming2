#include "DoorInteractable.h"
#include "Game.h"
#include "Level.h"
#include "pch.h"
#include <cassert>

DoorInteractable::DoorInteractable(const Vector2f &cell, const LevelBuilder &levelBuilder)
    : Interactable(cell), m_LevelBuilderFunc(levelBuilder), m_CustomSpawn()
{
    assert(levelBuilder && "Null levelBuilder passed");
}

DoorInteractable::DoorInteractable(const Vector2f &cell, const LevelBuilder &levelBuilder, Vector2f customSpawn)
    : Interactable(cell), m_LevelBuilderFunc(levelBuilder), m_CustomSpawn(customSpawn)
{
    assert(levelBuilder && "Null levelBuilder passed");
}

void DoorInteractable::Update(float delta)
{
}

void DoorInteractable::Draw() const
{
}

bool DoorInteractable::OnInteract(Game &game)
{
    Level *pLevel{game.SwitchLevel(m_LevelBuilderFunc())};
    if (m_CustomSpawn.has_value())
    {
        pLevel->SetSpawnPos(m_CustomSpawn.value());
    }
    return false;
}
