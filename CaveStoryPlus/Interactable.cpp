#include "Interactable.h"
#include "Player.h"
#include "Texture.h"
#include "utils.h"

Texture *Interactable::m_pSpriteSheetTexture{};
int Interactable::m_InstanceCount{};

Interactable::Interactable(const Vector2f &cell) : m_Region(Rectf{cell.x, cell.y, 1.f, 1.f})
{
    if (m_InstanceCount == 0)
    {
        m_pSpriteSheetTexture = new Texture("NpcSym.bmp");
    }

    ++m_InstanceCount;
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
