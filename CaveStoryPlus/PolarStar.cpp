#include "PolarStar.h"
#include "BulletManager.h"
#include "Texture.h"
#include "pch.h"
#include "utils.h"

PolarStar::PolarStar() : m_pTexture(new Texture("polarstar.png"))
{
}

PolarStar::~PolarStar()
{
    delete m_pTexture;
}

void PolarStar::Shoot(const Vector2f &handPos, Orientation orientation, BulletManager &manager)
{
    const float radians{utils::DegreesToRadians(static_cast<float>(orientation))};
    manager.SpawnPolarStarBullet(handPos, radians);
}

void PolarStar::Draw(const Vector2f &handPos, Orientation orientation) const
{
    glPushMatrix();
    glTranslatef(handPos.x, handPos.y, 0.f);
    glRotatef(static_cast<float>(orientation), 0.f, 0.f, 1.f);

    const float baseScale{0.03f};
    const bool needsFlipY{orientation == Orientation::west || orientation == Orientation::north};

    glScalef(baseScale, baseScale * (needsFlipY ? -1.f : 1.f), baseScale);
    m_pTexture->Draw(Vector2f{m_pTexture->GetWidth() * -0.5f, m_pTexture->GetHeight() * -0.5f});

    utils::SetColor(Color4f{1.f, 1.f, 0.f, 1.f});
    glPopMatrix();
}
