#include "PolarStar.h"
#include "Texture.h"
#include "utils.h"

PolarStar::PolarStar() : m_pTexture(new Texture("polestar.png"))
{
}

PolarStar::~PolarStar()
{
    delete m_pTexture;
}

void PolarStar::Shoot(const Vector2f &handPos, Orientation orientation)
{
}

void PolarStar::Draw(const Vector2f &handPos, Orientation orientation) const
{
    glPushMatrix();
    glTranslatef(handPos.x, handPos.y, 0.f);
    glRotatef(static_cast<float>(orientation), 0.f, 0.f, 1.f);
    glScalef(orientation == Orientation::east || orientation == Orientation::west ? -1.f : 1.f,
             orientation == Orientation::east ? 1.f : -1.f, 1.f);
    const float baseScale{0.03f};
    glScalef(baseScale, baseScale, baseScale);
    m_pTexture->Draw(Vector2f{m_pTexture->GetWidth() * -0.5f, m_pTexture->GetHeight() * -0.5f});
    utils::SetColor(Color4f{1.f, 1.f, 0.f, 1.f});
    glPopMatrix();
}