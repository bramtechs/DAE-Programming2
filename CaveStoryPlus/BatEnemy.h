#pragma once
#include "Enemy.h"
#include "Texture.h"
#include "structs.h"
#include <vector>

class Player;
class BatEnemy final : public Enemy
{
  public:
    explicit BatEnemy(std::vector<Vector2f> waypoints, float initialProgress = 0.5f);

    void InteractWithPlayer(Player &player) override;

    void Update(float delta) override;
    void Draw() const override;

    void DrawDebug() const override;

  private:
    Rectf GetAnimationSource(bool right, int frame) const;

    void PositionAlongRoute(float offset);

    float MeasureTotalDistance() const;

    std::vector<Vector2f> m_Waypoints{};
    float m_TimeElapsed{};
    bool m_LookingRight{};
    float m_MoveSpeed{1.25f};

    int m_AnimFrame{};
    float m_AnimTimeElapsed{};
    float m_TimePerFrame{0.2f};
};
