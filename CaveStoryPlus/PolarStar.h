#pragma once
#include "Weapon.h"

class Texture;
class BulletManager;
class PolarStar final : public Weapon
{
  public:
    explicit PolarStar();
    ~PolarStar() override;

    PolarStar(const PolarStar &) = delete;
    PolarStar &operator=(const PolarStar &) = delete;

    PolarStar(PolarStar &&) noexcept;
    PolarStar &operator=(PolarStar &&) noexcept;

    void Shoot(const Vector2f &handPos, Orientation orientation, BulletManager &manager) override;
    void Draw(const Vector2f &handPos, Orientation orientation) const override;

    float GetShootIntervalSeconds() const override
    {
        return 0.2f;
    }

  private:
    Texture *m_pTexture;
};
