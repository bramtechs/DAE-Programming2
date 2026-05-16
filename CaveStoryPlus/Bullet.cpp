#include "pch.h"
#include "Bullet.h"
#include "SDL_opengl.h"
#include "Texture.h"
#include "utils.h"

#include <cmath>

Bullet::Bullet(const Vector2f &position) : m_Position(position)
{
}

void Bullet::SetVelocity(const Vector2f &velocity)
{
    m_Velocity = velocity;
}

void Bullet::SetVelocityFromAngle(float angleRadians, float speed)
{
    m_Velocity.x = std::cos(angleRadians) * speed;
    m_Velocity.y = std::sin(angleRadians) * speed;
}

void Bullet::SetDamage(int damage)
{
    m_Damage = damage;
}

void Bullet::SetSourceRegion(const Rectf &region)
{
    m_SourceRegion = region;
}

void Bullet::SetScale(float scale)
{
    m_Scale = scale;
}

void Bullet::Update(float delta)
{
    m_Position += m_Velocity * delta;
}

float Bullet::GetAngleDegrees() const
{
    return utils::RadiansToDegrees(std::atan2f(m_Velocity.y, m_Velocity.x));
}

void Bullet::Draw(const Texture &texture) const
{
    glPushMatrix();
    glTranslatef(m_Position.x, m_Position.y, 0.f);
    glRotatef(GetAngleDegrees(), 0.f, 0.f, 1.f);
    glScalef(m_Scale, m_Scale, 1.f);

    texture.Draw(utils::RectWithCenter(Vector2f(0.f, 0.f), m_SourceRegion.width, m_SourceRegion.height),
                 m_SourceRegion);

    glPopMatrix();

#if 1 // debug graphics
    utils::SetColor(Color4f{1.f, 0.f, 0.f, 1.f});
    utils::FillRect(GetRegion());
    utils::SetColor(Color4f{0.f, 1.f, 0.f, 1.f});
    utils::DrawEllipse(GetCircleRegion(), 1.f);
#endif
}

Rectf Bullet::GetRegion() const
{
    Rectf region{};
    region.width = m_Scale * m_SourceRegion.width;
    region.height = m_Scale * m_SourceRegion.height;

    region.left = m_Position.x - region.width * 0.5f;
    region.bottom = m_Position.y - region.height * 0.5f;
    return region;
}

Circlef Bullet::GetCircleRegion() const
{
    const Rectf region{GetRegion()};
    const float size{std::min(region.width, region.height)};
    return Circlef(region.GetCenter(), size);
}

bool Bullet::IsOverlapping(const Rectf &region) const
{
    return utils::IsOverlapping(GetRegion(), region);
}

int Bullet::GetDamage() const
{
    return m_Damage;
}
