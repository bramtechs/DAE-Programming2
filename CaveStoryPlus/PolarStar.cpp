#include "PolarStar.h"
#include "BulletManager.h"
#include "SoundManager.h"
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

PolarStar::PolarStar(PolarStar &&o) noexcept : m_pTexture(o.m_pTexture)
{
    o.m_pTexture = nullptr;
}

PolarStar &PolarStar::operator=(PolarStar &&o) noexcept
{
    if (this != &o)
    {
        delete m_pTexture;

        m_pTexture = o.m_pTexture;
        o.m_pTexture = nullptr;
    }

    return *this;
}

void PolarStar::Shoot(const Vector2f &handPos, Orientation orientation, BulletManager &manager,
                      const SoundManager &sound)
{
    const float radians{utils::DegreesToRadians(static_cast<float>(orientation))};
    manager.SpawnPolarStarBullet(handPos, radians);
    sound.PlaySound(SoundManager::Effect::polar_star_shoot);
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
