#include "JumperEnemy.h"
#include "Player.h"
#include "PolygonCollider.h"
#include "Texture.h"
#include "pch.h"

const Rectf JumperEnemy::m_ChargingSourceRect{0.f, 0.f, 32.f, 32.f};
const Rectf JumperEnemy::m_IdleSourceRect{32.f, 0.f, 32.f, 32.f};
const Rectf JumperEnemy::m_JumpingSourceRect{64.f, 0.f, 32.f, 32.f};

JumperEnemy::JumperEnemy(const Vector2f &pos, Level &level) : Enemy(Vector2f{1.f, 1.f}), m_Level(level)
{
    SetCenter(pos);
}

void JumperEnemy::InteractWithPlayer(Player &player)
{
    Enemy::InteractWithPlayer(player);

    m_IsLookingRight = player.GetPosition().x > GetPosition().x;

    if (m_State == State::idle && player.GetPosition().Distance(GetCenter()) < m_ChargeRange)
    {
        m_State = State::charging;
    }
}

void JumperEnemy::Update(float delta)
{
    if (m_State == State::charging)
    {
        m_ChargeTimer += delta;
        if (m_ChargeTimer > m_ChargeTime)
        {
            m_State = State::jumping;
            m_LastPosition = GetPosition();
            m_ChargeTimer = 0.f;
            m_Velocity.x = m_IsLookingRight ? 1.f : -1.f;
            m_Velocity.y = m_JumpForce;
        }
    }
    else if (m_State == State::jumping)
    {
        Translate(m_Velocity * delta);
        m_Velocity.y -= m_Gravity * delta;

        PolygonCollider collider{};
        if (IsOverlappingLevel(collider))
        {
            SetPosition(m_LastPosition);
            if (m_Velocity.y <= 0.f && collider.IsPointAbove(GetPosition()))
            {
                m_State = State::idle;
            }
            else if (m_Velocity.y > 0.f)
            {
                m_Velocity.y = 0.f;
            }
        }
        else
        {
            m_LastPosition = GetPosition();
        }
    }
}

bool JumperEnemy::IsOverlappingLevel(PolygonCollider &outShape) const
{
    for (const PolygonCollider &collider : m_Level.GetColliders())
    {
        if (utils::IsOverlapping(collider.GetPolygon(), GetCircleRegion()))
        {
            outShape = collider;
            return true;
        }
    }

    return false;
}

void JumperEnemy::Draw() const
{
    GetSpriteSheet().Draw(GetRegion(), GetSourceRect());
}

void JumperEnemy::DrawDebug() const
{
    utils::SetColor(Color4f{1.f, 0.f, 0.f, 1.f});
    utils::DrawEllipse(GetCenter(), m_ChargeRange, m_ChargeRange);

    utils::SetColor(Color4f{0.f, 0.f, 1.f, 1.f});
    utils::DrawEllipse(GetCircleRegion());
}

Rectf JumperEnemy::GetSourceRect() const
{
    Rectf rect{};
    switch (m_State)
    {
    case State::idle:
        rect = m_IdleSourceRect;
        break;
    case State::charging:
        rect = m_ChargingSourceRect;
        break;
    case State::jumping:
        rect = m_JumpingSourceRect;
        break;
    }

    if (m_IsLookingRight)
    {
        rect.bottom += 32.f;
    }

    return rect;
}
