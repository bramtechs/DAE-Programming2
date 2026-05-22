#include "pch.h"
#include "HeartInteractable.h"
#include "Game.h"
#include "Player.h"

HeartInteractable::HeartInteractable(const Vector2f &cell) : Interactable(cell)
{
}

void HeartInteractable::Update(float delta)
{
    m_FlashInterval -= delta * 0.3f;
    m_Timer += delta;
}

void HeartInteractable::Draw() const
{
    const bool flashed{std::fmod(m_Timer, m_FlashInterval * 2.f) < m_FlashInterval};
    const Rectf source{GetAnimationFrameSource(flashed)};
    GetSpriteSheetTexture().Draw(GetRegion(), source);
}

bool HeartInteractable::OnTouch(Game &game)
{
    game.GetPlayer()->AddHealth(1);
    return true;
}

bool HeartInteractable::IsExpired() const
{
    return m_FlashInterval < 0.25f;
}

Rectf HeartInteractable::GetAnimationFrameSource(bool flashed) const
{
    Rectf cell{64.f, 160.f, 32.f, 32.f};
    if (flashed)
    {
        cell.left += cell.width;
        return cell;
    }
    else
    {
        return cell;
    }
}