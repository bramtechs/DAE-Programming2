#include "DecorInteractable.h"
#include "Game.h"
#include "Texture.h"
#include "pch.h"

DecorInteractable::DecorInteractable(const Rectf &region, const Rectf &sourceRect)
    : Interactable(Vector2f{region.left, region.bottom}, Vector2f{region.width, region.height}),
      m_SourceRect(sourceRect)
{
}

DecorInteractable::DecorInteractable(const Vector2f &cell, const Rectf &sourceRect)
    : Interactable(cell, Vector2f{sourceRect.width, sourceRect.height} / g_TileSize), m_SourceRect(sourceRect)
{
}

void DecorInteractable::Update(float delta)
{
}

void DecorInteractable::Draw() const
{
    GetSpriteSheetTexture().Draw(GetRegion(), m_SourceRect);
}

void DecorInteractable::SetSourceRect(const Rectf &region)
{
    m_SourceRect = region;
}
