#include "GoldInteractable.h"
#include "Texture.h"
#include "Vector2f.h"

GoldInteractable::GoldInteractable(const Vector2f &cell) : Interactable(cell, 0.75f)
{
}

void GoldInteractable::Update(float delta)
{
    m_AnimTimer += delta;

    if (m_AnimTimer > s_TimePerFrame)
    {
        m_AnimTimer = 0.f;
        ++m_AnimFrame;
    }
}

void GoldInteractable::Draw() const
{
    const Rectf srcRect{GetAnimationFrameSource()};
    GetSpriteSheetTexture().Draw(GetRegion(), srcRect);
}

bool GoldInteractable::Interact(Game &game)
{
    return true;
}

Rectf GoldInteractable::GetAnimationFrameSource() const
{
    const int rows{3};
    const int cols{5};
    const Rectf topLeftFrame{0.f, 32.f, 32.f, 32.f};

    const int frame{std::min(m_AnimFrame, rows * cols - 1)};
    const int row{frame / cols};
    const int col{frame % cols};

    Rectf result{topLeftFrame};
    result.left += col * result.width;
    result.bottom += row * result.height;
    return result;
}
