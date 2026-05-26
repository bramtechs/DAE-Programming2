#pragma once
#include "Enemy.h"

class BlockEnemy final : public Enemy
{
  public:
    explicit BlockEnemy(const Vector2f &pos);

    void InteractWithPlayer(Player &player) override;

    void Update(float delta) override;
    void Draw() const override;

    bool IsSolid() const override
    {
        return true;
    }

    int GetGoldDropCount() const override
    {
        return 0;
    }

  private:
    static const Rectf m_TextureSource;
};
