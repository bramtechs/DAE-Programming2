#include "pch.h"
#include "ReservoirSignInteractable.h"
#include "DialogManager.h"
#include "Game.h"

const Rectf ReservoirSignInteractable::m_TextureSourceRect{385.f, 130.f, 32.f, 31.f};

ReservoirSignInteractable::ReservoirSignInteractable(const Vector2f &tile)
    : DecorInteractable(tile, m_TextureSourceRect)
{
}

bool ReservoirSignInteractable::OnInteract(Game &game)
{
    game.GetDialogManager()->QueueMessage({"Reservoir"});
    return false;
}
