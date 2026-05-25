#include "pch.h"
#include "MimigaVillageNpc.h"
#include "DialogManager.h"
#include "Game.h"

Rectf MimigaVillageNpc::m_HidingSourceRegion{224.f, 384.f, 32.f, 32.f};
Rectf MimigaVillageNpc::m_TalkingSourceRegion{128.f, 416.f, 32.f, 32.f};

MimigaVillageNpc::MimigaVillageNpc(const Vector2f &cell) : DecorInteractable(cell, m_HidingSourceRegion)
{
}

bool MimigaVillageNpc::OnInteract(Game &game)
{
    switch (m_State)
    {
    case State::hiding: {
        DialogMessage &message{game.GetDialogManager()->QueueMessage({"....."})};
        message.SetReadEvent(new StopHidingDialogEvent(*this));
        break;
    }
    case State::talking: {
        DialogManager &manager{*game.GetDialogManager()};
        manager.QueueMessage({"What?", "You're not an enemy?", "I thought you were one of them..."});
        manager.QueueMessage({"My name is King.", "I'm the number one in this village.",
                              "Though I say number one, it doesn't really mean much.",
                              "There are only six of us left in the village."});
        manager.QueueMessage({"Well, really..."});
        DialogMessage &last{manager.QueueMessage({"...including Sue it's seven.", "But she's not one of us.",
                                                  "She's just an outsider that came into our village."})};
        last.SetReadEvent(new DoneTalkingDialogEvent(*this));
        break;
    }
    case State::doneTalking:
    default:
        break;
    }

    return false;
}

MimigaVillageNpc::StopHidingDialogEvent::StopHidingDialogEvent(MimigaVillageNpc &npc) : m_Npc(npc)
{
}

void MimigaVillageNpc::StopHidingDialogEvent::Execute(Game &game)
{
    m_Npc.m_State = State::talking;
    m_Npc.SetSourceRect(m_TalkingSourceRegion);
}

MimigaVillageNpc::DoneTalkingDialogEvent::DoneTalkingDialogEvent(MimigaVillageNpc &npc) : m_Npc(npc)
{
}

void MimigaVillageNpc::DoneTalkingDialogEvent::Execute(Game &game)
{
    m_Npc.m_State = State::doneTalking;
}
