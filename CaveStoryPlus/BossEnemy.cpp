#include "pch.h"
#include "BossEnemy.h"
#include "Texture.h"
#include "Game.h"

#include <cassert>

BossEnemy::BossEnemy(const Vector2f &pos) : Enemy(Vector2f{m_PixelsWidth / g_TileSize, m_PixelsHeight / g_TileSize})
{
    SetPosition(pos);
    CalcSourceRect();
}

void BossEnemy::Update(float delta)
{
    m_AnimTimer += delta;
    if (m_AnimTimer > m_SecondsPerFrame)
    {
        m_AnimTimer = 0.f;
        ++m_AnimFrame;
    }
    CalcSourceRect();
}

void BossEnemy::Draw() const
{
    GetSpriteSheet().Draw(GetRegion(), m_SourceRect);
}

void BossEnemy::CalcSourceRect()
{
    switch (m_State)
    {

    case State::talking: {
        m_SourceRect = Rectf(87.f, 274.f, m_PixelsWidth, m_PixelsHeight);
        return;
    }

    case State::running: {
        if (m_AnimFrame > 2)
        {
            m_AnimFrame = 0;
        }

        switch (m_AnimFrame)
        {
        case 0: {
            m_SourceRect = Rectf(9.f, 228.f, m_PixelsWidth, m_PixelsHeight);
            return;
        }
        case 1: {
            m_SourceRect = Rectf(89.f, 320.f, m_PixelsWidth, m_PixelsHeight);
            return;
        }
        case 2:
        default: {
            m_SourceRect = Rectf(8.f, 320.f, m_PixelsWidth, m_PixelsHeight);
            return;
        }
        }
        break;
    }

    case State::crushing: {
        if (m_AnimFrame > 1)
        {
            m_AnimFrame = 0;
        }

        switch (m_AnimFrame)
        {
        case 0: {
            m_SourceRect = Rectf(170.f, 327.f, m_PixelsWidth, m_PixelsHeight);
            return;
        }
        case 1:
        default: {
            m_SourceRect = Rectf(248.f, 327.f, m_PixelsWidth, m_PixelsHeight);
            return;
        }
        }
        break;
    }

    case State::jumping: {
        m_SourceRect = Rectf(248.f, 224.f, m_PixelsWidth, m_PixelsHeight);
        return;
    }
    }

    assert(0 && "Fell through");
}
