#include "pch.h"
#include "PickupInteractable.h"
#include "DialogManager.h"
#include "Game.h"
#include "Texture.h"

#include <algorithm>

PickupInteractable::PickupInteractable(const Vector2f &cell) : Interactable(cell)
{
}

void PickupInteractable::Update(float delta)
{
    m_AnimationTimer += delta;

    if (m_AnimationTimer > m_TimePerFrame)
    {
        m_CurrentFrame += 1;
        if (m_CurrentFrame > 3)
        {
            m_CurrentFrame = 0;
        }
        m_AnimationTimer = 0.f;
    }
}

void PickupInteractable::Draw() const
{
    const Rectf animSource{GetAnimationFrameSource(m_CurrentFrame)};
    GetSpriteSheetTexture().Draw(GetRegion(), animSource);
}

bool PickupInteractable::OnInteract(Game &game)
{
    game.GetDialogManager()->QueueMessage("Something shines brightly...");
    game.GetDialogManager()->QueueMessage("Obtained the Silver Locket.");
    return true;
}

Rectf PickupInteractable::GetAnimationFrameSource(int frame)
{
    frame = std::clamp(frame, 0, 3);
    Rectf first{193.f, 96.f, 32.f, 32.f};
    first.left += first.width * frame;
    return first;
}
