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

void Bullet::SetDamage(float damage)
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
}
