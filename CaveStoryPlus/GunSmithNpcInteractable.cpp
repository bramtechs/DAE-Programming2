#include "pch.h"
#include "GunSmithNpcInteractable.h"
#include "Game.h"
#include "DialogManager.h"
#include "structs.h"

GunSmithNpcInteractable::GunSmithNpcInteractable(const Vector2f &cell)
    : DecorInteractable(cell, Rectf{225.f, 448.f, 32.f, 32.f})
{
}

bool GunSmithNpcInteractable::OnInteract(Game &game)
{
    game.GetDialogManager()->QueueMessage({"ZZZzzz...zzz..."});
    return false;
}
