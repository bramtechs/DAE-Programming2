#include "LifeCapsuleInteractable.h"
#include "DialogManager.h"
#include "DialogEvent.h"
#include "Game.h"
#include "Player.h"
#include "Texture.h"
#include "pch.h"

LifeCapsuleInteractable::LifeCapsuleInteractable(const Vector2f &cell) : Interactable(cell)
{
}

void LifeCapsuleInteractable::Update(float delta)
{
    m_AnimTimer += delta;

    const float timePerFrame{0.2f};
    if (m_AnimTimer > timePerFrame)
    {
        m_FrameIndex = (m_FrameIndex + 1) % 2;
        m_AnimTimer = 0.f;
    }
}

void LifeCapsuleInteractable::Draw() const
{
    const Rectf srcRect{GetAnimationSource(m_FrameIndex)};
    GetSpriteSheetTexture().Draw(GetRegion(), srcRect);
}

bool LifeCapsuleInteractable::OnInteract(Game &game)
{
    DialogMessage &msg{game.GetDialogManager()->QueueMessage({"Obtained a Life Capsule.", "Max life increased by 3."})};
    msg.SetReadEvent(new GiveMaxHealthDialogEvent(3));
    return true;
}

Rectf LifeCapsuleInteractable::GetAnimationSource(int frame) const
{
    const float tileSize{32};
    const int col{2 + frame};
    const int row{6};
    return Rectf{static_cast<float>(col * tileSize), static_cast<float>(row * tileSize), tileSize, tileSize};
}

LifeCapsuleInteractable::GiveMaxHealthDialogEvent::GiveMaxHealthDialogEvent(int amount) : m_Amount(amount)
{
}

void LifeCapsuleInteractable::GiveMaxHealthDialogEvent::Execute(Game &game)
{
    game.GetPlayer()->AddMaxHealth(m_Amount);
}
