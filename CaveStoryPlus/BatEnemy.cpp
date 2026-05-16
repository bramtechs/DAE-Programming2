#include "BatEnemy.h"
#include "Player.h"
#include "pch.h"
#include "utils.h"

BatEnemy::BatEnemy(std::vector<Vector2f>&& waypoints, float initialProgress)
    : Enemy(Vector2f{0.8f, 0.8f}), m_Waypoints(std::move(waypoints))
{
    m_TimeElapsed = MeasureTotalDistance() * initialProgress;
}

void BatEnemy::InteractWithPlayer(Player &player)
{
    Enemy::InteractWithPlayer(player);
    m_LookingRight = player.GetPosition().x > m_Position.x;
}

void BatEnemy::Update(float delta)
{
    m_TimeElapsed += delta;
    PositionAlongRoute(
        utils::SineBetween(m_TimeElapsed, MeasureTotalDistance() / m_MoveSpeed, 0.f, MeasureTotalDistance()));

    m_AnimTimeElapsed += delta;
    if (m_AnimTimeElapsed > m_TimePerFrame)
    {
        m_AnimTimeElapsed = 0.f;
        m_AnimFrame = (m_AnimFrame + 1) % 2;
    }
}

void BatEnemy::Draw() const
{
    const Rectf source{GetAnimationSource(m_LookingRight, m_AnimFrame)};
    GetSpriteSheet().Draw(GetRegion(), source);
}

void BatEnemy::DrawDebug() const
{
    Enemy::DrawDebug();

    utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
    utils::DrawRect(GetRegion());

    utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));

    for (int i{0}; i < m_Waypoints.size(); ++i)
    {
        if (i < static_cast<int>(m_Waypoints.size()) - 1)
        {
            utils::DrawLine(m_Waypoints[i], m_Waypoints[i + 1], 1.f);
        }

        const float size{0.2f};
        const Rectf marker{utils::RectWithCenter(m_Waypoints[i], size, size)};
        utils::FillRect(marker);
    }
}

Rectf BatEnemy::GetAnimationSource(bool right, int frame) const
{
    const float tileSize{32.f};
    const int x{2 + frame};
    const int y{2 + (right ? 1 : 0)};
    return Rectf{static_cast<float>(x * tileSize), //
                 static_cast<float>(y * tileSize), tileSize, tileSize};
}

void BatEnemy::PositionAlongRoute(float offset)
{
    float accumulated{};
    for (int i{}; i < static_cast<int>(m_Waypoints.size()) - 1; ++i)
    {
        float segmentLength{m_Waypoints[i].Distance(m_Waypoints[i + 1])};
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
