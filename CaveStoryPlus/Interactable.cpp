#include "Interactable.h"
#include "Player.h"
#include "utils.h"

Interactable::Interactable(const Vector2f &cell) : m_Region(Rectf{cell.x, cell.y, 1.f, 1.f})
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
