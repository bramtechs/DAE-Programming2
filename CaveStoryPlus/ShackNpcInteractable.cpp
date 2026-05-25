#include "pch.h"
#include "ShackNpcInteractable.h"
#include "Game.h"
#include "Level.h"
#include "BossEnemy.h"
#include "DialogManager.h"

Rectf ShackNpcInteractable::m_HidingSourceRegion{256.f, 385.f, 32.f, 32.f};
Rectf ShackNpcInteractable::m_TalkingSourceRegion{256.f, 417.f, 32.f, 32.f};

ShackNpcInteractable::ShackNpcInteractable(const Vector2f &cell) : DecorInteractable(cell, m_HidingSourceRegion)
{
}

bool ShackNpcInteractable::OnInteract(Game &game)
{
    if (m_DoneTalking)
    {
        return false;
    }

    DialogManager &man{*game.GetDialogManager()};
    man.QueueMessage({"Waaaaaaaaaa!"});
    man.QueueMessage({"Oh, help me!", "Help me!"});

    man.QueueMessage({"...  ?"}).AttachCallback([this](Game &) { //
        SetSourceRect(m_TalkingSourceRegion);
    });

    man.QueueMessage({"You're not the Doctor?"});
    man.QueueMessage({"Oh, sorry 'bout that.", "The Doctor's such a cruel and evil person.",
                      "He shows up in the village and kidnaps Mimiga... at times even killing someone."});
    man.QueueMessage({"The Doctor--he killed my older brother."});
    man.QueueMessage({"Ah!", "That pendant!"});
    man.QueueMessage({"You picked it up for me?", "Sue gave it to me!"});
    man.QueueMessage({"..."});

    man.QueueMessage({"But. I don't want it anymore.", "King gets bent out of shape when Sue and I get along.",
                      "Please keep it."})
        .AttachCallback([](Game &game) { //
            game.GetActiveLevel()->SpawnEnemy(new BossEnemy(Vector2f{5.f, 6.72f}));
        });

    man.QueueMessage({"Oh Yeaaah!!"});
    man.QueueMessage({"I found you."});
    man.QueueMessage({"It's no use hiding from me.", "I've got the nose of a clever Harrier!"})
        .AttachCallback([this](Game &) { //
            SetSourceRect(m_HidingSourceRegion);
            m_DoneTalking = true;
        });

    return false;
}
