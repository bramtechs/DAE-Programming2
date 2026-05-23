#include "pch.h"
#include "ShackNpcInteractable.h"
#include "Game.h"
#include "DialogManager.h"

Rectf ShackNpcInteractable::m_HidingSourceRegion{256.f, 385.f, 32.f, 32.f};
Rectf ShackNpcInteractable::m_TalkingSourceRegion{256.f, 417.f, 32.f, 32.f};

ShackNpcInteractable::ShackNpcInteractable(const Vector2f &cell) : DecorInteractable(cell, m_HidingSourceRegion)
{
}

bool ShackNpcInteractable::OnInteract(Game &game)
{
    DialogManager &manager{*game.GetDialogManager()};
    manager.QueueMessage("Waaaaaaaaaa!");
    manager.QueueMessage({"Oh, help me!", "Help me!"});
    manager.QueueMessage("...  ?");
    manager.QueueMessage("You're not the Doctor?");
    manager.QueueMessage({"Oh, sorry 'bout that.", "The Doctor's such a cruel and evil person.",
                          "He shows up in the village and kidnaps Mimiga... at times even killing someone."});
    manager.QueueMessage("The Doctor--he killed my older brother.");
    manager.QueueMessage({"Ah!", "That pendant!"});
    manager.QueueMessage({"You picked it up for me?", "Sue gave it to me!"});
    manager.QueueMessage("...");
    manager.QueueMessage(
        {"But. I don't want it anymore.", "King gets bent out of shape when Sue and I get along.", "Please keep it."});

    manager.QueueMessage({"Oh Yeaaah!!"});
    manager.QueueMessage("I found you.");
    manager.QueueMessage({"It's no use hiding from me.", "I've got the nose of a clever Harrier!"});

    return false;
}
