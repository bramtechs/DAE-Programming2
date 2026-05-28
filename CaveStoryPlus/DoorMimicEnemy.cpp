#include "pch.h"
#include "DoorMimicEnemy.h"
#include "Player.h"
#include "utils.h"

const float DoorMimicEnemy::m_MaxPlayerDistance{8.f};

DoorMimicEnemy::DoorMimicEnemy(const Vector2f &pos) : Enemy(Vector2f{1.f, 1.8f})
{
    SetPosition(pos);
}

void DoorMimicEnemy::InteractWithPlayer(Player &player)
{
    Enemy::InteractWithPlayer(player);
    m_PlayerDistance = utils::GetDistance(GetPosition(), player.GetPosition());
}

void DoorMimicEnemy::Update(float delta)
{
}

void DoorMimicEnemy::Draw() const
{
    GetSpriteSheet().Draw(GetRegion(), GetAnimationSource());
}

Rectf DoorMimicEnemy::GetAnimationSource() const
{
    if (m_AttackedTimer > 0.f)
    {
        return Rectf{324.f, 81.f, 30.f, 46.f};
    }

    if (m_PlayerDistance < m_MaxPlayerDistance / 2.f)
    {
        // eye open
        return Rectf{292.f, 81.f, 30.f, 46.f};
    }
    else if (m_PlayerDistance < m_MaxPlayerDistance)
    {
        // eye slightly open
        return Rectf{260.f, 81.f, 30.f, 46.f};
    }

    return Rectf{228.f, 80.f, 30.f, 47.f};
}
