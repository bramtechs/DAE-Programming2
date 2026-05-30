#include "SpikeInteractable.h"
#include "Game.h"
#include "Player.h"
#include "pch.h"

SpikeInteractable::SpikeInteractable(const Vector2f &cell, Orientation orientation)
    : Interactable(cell, 0.6f), m_Orientation(orientation)
{
}

void SpikeInteractable::Update(float delta)
{
}

void SpikeInteractable::Draw() const
{
    GetSpriteSheetTexture().Draw(GetTileRegion(), GetSourceRegion());
}

bool SpikeInteractable::OnTouch(Game &game)
{
    Player *pPlayer{game.GetPlayer()};
    if (pPlayer)
    {
        pPlayer->DealDamage(2);
    }

    return false;
}

Rectf SpikeInteractable::GetSourceRegion() const
{
    Rectf cell{512.f, 400.f, 32.f, 32.f};

    switch (m_Orientation)
    {
    case Orientation::floor:
        cell.left += cell.width;
        break;
    case Orientation::ceiling:
        cell.left += cell.width * 3.f;
        break;
    case Orientation::leftWall:
        cell.left += cell.width * 2.f;
        break;
    case Orientation::rightWall:
        break;
    }

    return cell;
}
