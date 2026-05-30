#include "pch.h"
#include "ShackNpcInteractable.h"
#include "Game.h"
#include "Level.h"
#include "BossEnemy.h"
#include "DialogManager.h"

const Rectf ShackNpcInteractable::m_HidingSourceRegion{256.f, 385.f, 32.f, 32.f};
const Rectf ShackNpcInteractable::m_TalkingSourceRegion{256.f, 417.f, 32.f, 32.f};

ShackNpcInteractable::ShackNpcInteractable(const Vector2f &cell) : DecorInteractable(cell, m_HidingSourceRegion)
{
}

void ShackNpcInteractable::Update(float delta)
{
    if (!m_DoneTalking && m_pDialogManager && !m_pDialogManager->IsDialogOpen())
    {
        SetSourceRect(m_HidingSourceRegion);
        m_DoneTalking = true;
    }
}

bool ShackNpcInteractable::OnInteract(Game &game)
{
    m_pDialogManager = game.GetDialogManager();
    if (m_DoneTalking)
    {
        return false;
    }

    DialogManager &man{*game.GetDialogManager()};
    man.QueueMessage({"Waaaaaaaaaa!"});
    man.QueueMessage({"Oh, help me!", "Help me!"});

    man.QueueMessage({"...  ?"}).SetReadEvent(new StartTalkingDialogEvent(*this));

    man.QueueMessage({"You're not the Doctor?"});
    man.QueueMessage({"Oh, sorry 'bout that.", "The Doctor's such a cruel and evil person.",
                      "He shows up in the village and kidnaps Mimiga...", "at times even killing someone."});
    man.QueueMessage({"The Doctor--he killed my older brother."});
    man.QueueMessage({"Ah!", "That pendant!"});
    man.QueueMessage({"You picked it up for me?", "Sue gave it to me!"});
    man.QueueMessage({"..."});

    man.QueueMessage({"But. I don't want it anymore.", "King gets bent out of shape when Sue and I get along.",
                      "Please keep it."})
        .SetReadEvent(new SpawnBossEnemyDialogEvent(*this));

    man.QueueMessage({"Oh Yeaaah!!"});
    man.QueueMessage({"I found you."});
    man.QueueMessage({"It's no use hiding from me.", "I've got the nose of a clever Harrier!"});

    return false;
}

// StartTalkingDialogEvent

ShackNpcInteractable::StartTalkingDialogEvent::StartTalkingDialogEvent(ShackNpcInteractable &npc) : m_Npc(npc)
{
}

void ShackNpcInteractable::StartTalkingDialogEvent::Execute(Game &game)
{
    m_Npc.SetSourceRect(m_TalkingSourceRegion);
}

// SpawnBossEnemyDialogEvent

ShackNpcInteractable::SpawnBossEnemyDialogEvent::SpawnBossEnemyDialogEvent(ShackNpcInteractable &npc) : m_Npc(npc)
{
}

void ShackNpcInteractable::SpawnBossEnemyDialogEvent::Execute(Game &game)
{
    BossEnemy *pBoss{new BossEnemy(Vector2f{5.f, 6.72f}, 5.f, 17.f)};
    game.GetActiveLevel()->SpawnEnemy(pBoss);
    pBoss->StartAttacking(*game.GetPlayer(), game);

    game.GetMusicManager().SwitchTrack(MusicManager::Track::boss);
}
