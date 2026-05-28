#pragma once
#include "Enemy.h"

class DoorMimicEnemy final : public Enemy
{
  public:
    explicit DoorMimicEnemy(const Vector2f &pos);

    void InteractWithPlayer(Player &player) override;

    void Update(float delta) override;
    void Draw() const override;

  private:
    virtual int GetGoldDropCount() const
    {
        return 2;
    }

    Rectf GetAnimationSource() const;

    float m_PlayerDistance{};
    float m_AttackedTimer{};

    static const float m_MaxPlayerDistance;
};
