#include "LifeCapsule.h"

#include <iostream>

LifeCapsule::LifeCapsule(const Vector2f &cell) : Interactable(cell)
{
}

void LifeCapsule::Interact(const GameContext &context)
{
    std::cout << "Collected life capsule" << std::endl;
}
