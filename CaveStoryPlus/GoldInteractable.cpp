#include "pch.h"
#include "GoldInteractable.h"
#include "Game.h"
#include "Level.h"
#include "Player.h"
#include "Texture.h"
#include "Vector2f.h"
#include "utils.h"

GoldInteractable::GoldInteractable(const Vector2f &cell, Level &level) : Interactable(cell, 0.75f), m_Level(level)
{
    m_Velocity = Vector2f{utils::RandomFloat(-1.f, 1.f), 0.f};
}

void GoldInteractable::Update(float delta)
{
    m_AnimTimer += delta;

    if (m_AnimTimer > m_TimePerFrame)
    {
        m_AnimTimer = 0.f;
        ++m_AnimFrame;
    }

    m_Velocity.y += m_Gravity * delta;
    m_Velocity.x = utils::EaseTowards(m_Velocity.x, 0.f, delta);

    if (m_Velocity.y < 0.f)
    {
        for (const PolygonCollider &collider : m_Level.GetColliders())
        {
            if (collider.Overlaps(GetHitbox()))
            {
                m_Velocity.y *= -1.f;
                m_Velocity.y /= 2.f;
                break;
            }
        }
    }

    Translate(m_Velocity * delta);
}

void GoldInteractable::Draw() const
{
    const Rectf srcRect{GetAnimationFrameSource()};
    GetSpriteSheetTexture().Draw(GetRegion(), srcRect);
}

bool GoldInteractable::OnTouch(Game &game)
{
    game.GetPlayer()->AddGold();
    return true;
}

Rectf GoldInteractable::GetAnimationFrameSource() const
{
    const int rows{3};
    const int cols{5};
    const Rectf topLeftFrame{0.f, 32.f, 32.f, 32.f};

    const int frame{std::min(m_AnimFrame, rows * cols - 1)};
    const int row{frame / cols};
    const int col{frame % cols};

    Rectf result{topLeftFrame};
    result.left += col * result.width;
    result.bottom += row * result.height;
    return result;
}

Circlef GoldInteractable::GetHitbox() const
{
    const Rectf region{GetRegion()};
    return Circlef(GetCenter(), std::max(region.width, region.height) * 0.5f);
}
