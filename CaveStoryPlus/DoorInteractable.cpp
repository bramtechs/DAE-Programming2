#include "DoorInteractable.h"
#include "Game.h"
#include "pch.h"
#include <cassert>

DoorInteractable::DoorInteractable(const Vector2f &cell, const std::function<Level *()> &levelBuilder)
    : Interactable(cell), m_LevelBuilderFunc(levelBuilder)
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
    game.SwitchLevel(m_LevelBuilderFunc());
    return false;
}
