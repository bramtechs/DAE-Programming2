#pragma once
#include "Enemy.h"
#include <vector>

class BatEnemy final : public Enemy
{
public:
	BatEnemy(std::vector<Vector2f> waypoints, float initialProgress = 0.5f);

	void Update(float delta) override;
	void Draw() const override;

	void DrawDebug() const override;

private:
	void PositionAlongRoute(float offset);

	float MeasureTotalDistance() const;

	std::vector<Vector2f> m_Waypoints{};
	float m_TimeElapsed{};
	float m_MoveSpeed{1.25f};
};

