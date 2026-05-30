#include "ChestInteractable.h"
#include "DialogManager.h"
#include "SoundManager.h"
#include "Game.h"
#include "Player.h"
#include "PolarStar.h"
#include "pch.h"

const Rectf ChestInteractable::s_ClosedSourceRect{481.f, 0.f, 32.f, 32.f};
const Rectf ChestInteractable::s_OpenSourceRect{449.f, 81.f, 32.f, 16.f};

ChestInteractable::ChestInteractable(const Vector2f &cell) : Interactable(Rectf{cell.x, cell.y, 1.f, 0.5f})
{
}

void ChestInteractable::SetOpened(bool open)
{
    m_IsOpened = open;
}

void ChestInteractable::Update(float delta)
{
}

void ChestInteractable::Draw() const
{
    if (m_IsOpened)
    {
        GetSpriteSheetTexture().Draw(GetRegion(), s_OpenSourceRect);
    }
    else
    {
        GetSpriteSheetTexture().Draw(GetTileRegion(), s_ClosedSourceRect);
    }
}

bool ChestInteractable::OnInteract(Game &game)
{
    if (!m_IsOpened)
    {
        Player *pPlayer{game.GetPlayer()};
        if (pPlayer)
        {
            game.GetSoundManager()->PlaySound(SoundManager::Effect::chest_open);

            DialogManager &dialogs{*game.GetDialogManager()};
            dialogs.QueueMessage({"Opened the treasure chest."});
            dialogs.QueueMessage({"Obtained the Polar Star."});

            pPlayer->HoldWeapon(new PolarStar());
            m_IsOpened = true;
        }
    }
    return false;
}
