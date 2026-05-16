#pragma once
#include "Enemy.h"

class BlockEnemy final : public Enemy
{
  public:
    explicit BlockEnemy(const Vector2f &pos);
    BlockEnemy(const BlockEnemy &) = delete;
    BlockEnemy(BlockEnemy &&) = delete;
    BlockEnemy &operator=(const BlockEnemy &) = delete;
    BlockEnemy &operator=(BlockEnemy &) = delete;

    void InteractWithPlayer(Player &player) override;

    void Update(float delta) override;
    void Draw() const override;

    bool IsSolid() const override
    {
        return true;
    }

  private:
    static const Rectf m_TextureSource;
};
