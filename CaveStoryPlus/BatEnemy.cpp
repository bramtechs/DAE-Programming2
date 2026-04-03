#include "pch.h"
#include "BatEnemy.h"
#include "utils.h"

BatEnemy::BatEnemy(std::vector<Vector2f> waypoints, float initialProgress)
	: Enemy(Vector2f{ 1.f,1.f }), m_Waypoints(std::move(waypoints))
{
	m_TimeElapsed = MeasureTotalDistance() * initialProgress;
}

void BatEnemy::Update(float delta)
{
	m_TimeElapsed += delta;
	PositionAlongRoute(utils::SineBetween(m_TimeElapsed, MeasureTotalDistance() / m_MoveSpeed, 0.f, MeasureTotalDistance()));
}

void BatEnemy::Draw() const
{
}

void BatEnemy::DrawDebug() const
{
	Enemy::DrawDebug();

	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	utils::DrawRect(GetRegion());

	utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));

	for (int i{ 0 }; i < m_Waypoints.size(); ++i)
	{
		if (i < static_cast<int>(m_Waypoints.size()) - 1)
		{
			utils::DrawLine(m_Waypoints[i], m_Waypoints[i + 1], 1.f);
		}

		const float size{ 0.2f };
		const Rectf marker{ utils::RectWithCenter(m_Waypoints[i], size, size) };
		utils::FillRect(marker);
	}

}

void BatEnemy::PositionAlongRoute(float offset)
{
	float accumulated{};
	for (int i{}; i < static_cast<int>(m_Waypoints.size()) - 1; ++i)
	{
		float segmentLength{ m_Waypoints[i].Distance(m_Waypoints[i + 1]) };
		if (accumulated + segmentLength >= offset)
		{
			m_Position = m_Waypoints[i].MoveTowards(m_Waypoints[i + 1], offset - accumulated);
			return;
		}
		accumulated += segmentLength;
	}

	m_Position = m_Waypoints.back();
}

float BatEnemy::MeasureTotalDistance() const
{
	float distance{};
	for (int i{}; i < static_cast<int>(m_Waypoints.size()) - 1; ++i)
	{
		distance += m_Waypoints[i].Distance(m_Waypoints[i + 1]);
	}
	return distance;
}
