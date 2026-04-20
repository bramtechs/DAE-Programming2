#include "Door.h"
#include "Game.h"
#include "LevelBuilder.h"

Door::Door(const Vector2f &cell, const std::function<Level *()> &levelBuilder)
    : Interactable(cell), m_LevelBuilderFunc(levelBuilder)
{
}

void Door::Update(float delta)
{
}

void Door::Draw() const
{
}

void Door::Interact(Game &game)
{
    LevelBuilder builder{};
    game.SwitchLevel(m_LevelBuilderFunc());
}
