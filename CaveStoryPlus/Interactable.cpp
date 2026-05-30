#include "Interactable.h"
#include "Player.h"
#include "Texture.h"
#include "pch.h"
#include "utils.h"

#include <cassert>

Interactable::Interactable(const Rectf &region) : m_Region(region)
{
}

Interactable::Interactable(const Vector2f &cell, const Vector2f &size)
    : Interactable(utils::RectWithCenter(cell + Vector2f{0.5f, 0.5f}, size.x, size.y))
{
}

Interactable::Interactable(const Vector2f &cell, float size) : Interactable(cell, Vector2f{size, size})
{
}

bool Interactable::IsInside(const Player &player) const
{
    return utils::IsOverlapping(player.GetRegion(), m_Region);
}

void Interactable::DrawDebug() const
{
    utils::SetColor(Color4f(0.f, 1.f, 1.f, 1.f));
    utils::DrawRect(m_Region, 2.f);
}

void Interactable::Translate(const Vector2f &offset)
{
    m_Region.left += offset.x;
    m_Region.bottom += offset.y;
}

void Interactable::SetSpriteSheetTexture(const Texture &texture)
{
    m_pSpriteSheetTexture = &texture;
}

Rectf Interactable::GetRegion() const
{
    return m_Region;
}

Rectf Interactable::GetTileRegion() const
{
    const int cellX{static_cast<int>(m_Region.left)};
    const int cellY{static_cast<int>(m_Region.bottom)};
    return Rectf{static_cast<float>(cellX), static_cast<float>(cellY), 1.f, 1.f};
}

Vector2f Interactable::GetCenter() const
{
    return Vector2f{m_Region.left + m_Region.width * 0.5f, m_Region.bottom + m_Region.height * 0.5f};
}

const Texture &Interactable::GetSpriteSheetTexture() const
{
    assert(m_pSpriteSheetTexture && "Texture not set");
    return *m_pSpriteSheetTexture;
}

void Interactable::SetRegion(const Rectf &region)
{
    m_Region = region;
}

Vector2f Interactable::GetPosition() const
{
    return Vector2f{m_Region.left, m_Region.bottom};
}
