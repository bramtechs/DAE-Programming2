#include "pch.h"
#include "DoorInteractable.h"
#include "Game.h"
#include "LevelBuilder.h"
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

bool DoorInteractable::Interact(Game &game)
{
    LevelBuilder builder{};
    game.SwitchLevel(m_LevelBuilderFunc());
    return false;
}
