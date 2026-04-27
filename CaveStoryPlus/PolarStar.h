#pragma once
#include "Weapon.h"

class Texture;
class PolarStar final : public Weapon
{
  public:
    PolarStar();
    ~PolarStar() override;
    PolarStar(const PolarStar&) = delete;
    PolarStar(PolarStar&&) noexcept = delete;
    PolarStar& operator=(PolarStar&&) = delete;
    PolarStar& operator=(const PolarStar&) = delete;

    void Shoot(const Vector2f &handPos, Orientation orientation) override;
    void Draw(const Vector2f &handPos, Orientation orientation) const override;

private:
    Texture *m_pTexture;
};