#include "LifeCapsule.h"
#include "Texture.h"
#include <iostream>

LifeCapsule::LifeCapsule(const Vector2f &cell) : Interactable(cell)
{
}

void LifeCapsule::Update(float delta)
{
    m_AnimTimer += delta;

    const float timePerFrame{0.2f};
    if (m_AnimTimer > timePerFrame)
    {
        m_FrameIndex = (m_FrameIndex + 1) % 2;
        m_AnimTimer = 0.f;
    }
}

void LifeCapsule::Draw() const
{
    const Rectf srcRect{GetAnimationSource(m_FrameIndex)};
    GetSpriteSheetTexture().Draw(GetRegion(), srcRect);
}

void LifeCapsule::Interact(const GameContext &context)
{
    std::cout << "Collected life capsule" << std::endl;
}

Rectf LifeCapsule::GetAnimationSource(int frame) const
{
    const float tileSize{32};
    const int col{2 + frame};
    const int row{6};
    return Rectf{static_cast<float>(col * tileSize), static_cast<float>(row * tileSize), tileSize, tileSize};
}
