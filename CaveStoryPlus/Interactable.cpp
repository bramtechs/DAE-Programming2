#include "pch.h"
#include "Interactable.h"
#include "Player.h"
#include "Texture.h"
#include "utils.h"

Texture *Interactable::m_pSpriteSheetTexture{};
int Interactable::m_InstanceCount{};

Interactable::Interactable(const Vector2f &cell, const Vector2f &size) : m_Region(Rectf{cell.x, cell.y, size.x, size.y})
{
    if (m_InstanceCount == 0)
    {
        m_pSpriteSheetTexture = new Texture("NpcSym.bmp");
    }

    ++m_InstanceCount;
}

Interactable::Interactable(const Vector2f &cell, float size) : Interactable(cell, Vector2f{size, size})
{
}

Interactable::~Interactable()
{
    --m_InstanceCount;

    if (m_InstanceCount == 0)
    {
        delete m_pSpriteSheetTexture;
    }
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

Rectf Interactable::GetRegion() const
{
    return m_Region;
}

Vector2f Interactable::GetCenter() const
{
    return Vector2f{m_Region.left + m_Region.width * 0.5f, m_Region.bottom + m_Region.height * 0.5f};
}
