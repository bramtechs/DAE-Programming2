#include "pch.h"
#include "BossEnemy.h"
#include "Texture.h"
#include "DialogManager.h"
#include "Player.h"
#include "Game.h"

#include <cassert>

const Rectf BossEnemy::m_BossLabelSourceRect{487.f, 322.f, 58.f, 14.f};
const int BossEnemy::m_PixelsWidth{66};
const int BossEnemy::m_PixelsHeight{45};
const float BossEnemy::m_SecondsPerFrame{0.2f};
const float BossEnemy::m_MovementAccel{1.35f};
const float BossEnemy::m_SecondsBetweenJumps{3.f};
const float BossEnemy::m_SecondsCrushing{2.f};
const float BossEnemy::m_JumpForce{5.f};

BossEnemy::BossEnemy(const Vector2f &pos, float areaLeft, float areaRight)
    : Enemy(Vector2f{m_PixelsWidth / g_TileSize, m_PixelsHeight / g_TileSize}), m_FloorTop(pos.y), m_AreaLeft(areaLeft),
      m_AreaRight(areaRight)
{
    SetPosition(pos);
    SetHealth(m_MaxHealth);
    CalcSourceRect(false);
}

void BossEnemy::Update(float delta)
{
    UpdateAnimations(delta);

    if (m_pPlayer == nullptr)
    {
        assert(0 && "No player to attack");
        return;
    }

    switch (m_State)
    {
    case State::moving: {
        const Vector2f target{m_pPlayer->GetPosition()};
        Vector2f dir{(m_pPlayer->GetPosition() - GetPosition()).Normalized()};
        dir.y = 0.f;

        m_Velocity += dir * delta * m_MovementAccel;

        m_JumpTimer -= delta;
        if (m_JumpTimer < 0.f)
        {
            const float part{m_SecondsBetweenJumps * 0.1f};
            m_JumpTimer = m_SecondsBetweenJumps + utils::RandomFloat(-part, part);

            m_Velocity.y += m_JumpForce;
        }

        if (utils::IsOverlapping(GetRegion(), m_pPlayer->GetRegion()))
        {
            m_State = State::crushing;
            m_CrushingTimer = m_SecondsCrushing;
        }

        break;
    }

    case State::crushing: {
        m_Velocity.x = 0.f;
        m_CrushingTimer -= delta * 2.f;
        if (m_CrushingTimer < 0.f)
        {
            m_State = State::moving;
        }

        break;
    }

    default:
        break;
    }

    // respect horizontal bounds
    if (GetPosition().x < m_AreaLeft)
    {
        Translate(Vector2f{m_AreaLeft - GetPosition().x, 0.f});
        if (m_Velocity.x < 0.f)
        {
            m_Velocity.x = 0;
        }
    }
    else if (GetPosition().x > m_AreaRight)
    {
        Translate(Vector2f{m_AreaRight - GetPosition().x, 0.f});
        if (m_Velocity.x > 0.f)
        {
            m_Velocity.x = 0;
        }
    }

    // apply gravity
    m_Velocity.y -= delta * 9.8f * (m_State == State::fleeing ? -1.f : 1.f);

    const float heightAboveFloor{GetPosition().y - m_FloorTop};
    if (heightAboveFloor < 0.f)
    {
        m_Velocity.y = 0.f;
        Translate(Vector2f{0.f, -heightAboveFloor});
    }
    else if (m_pGame && m_State == State::fleeing && heightAboveFloor > 30.f)
    {
        m_pGame->GetDialogManager()->QueueMessage({"(You won.)"});
        m_State = State::done;
    }

    Translate(m_Velocity * delta);
    const float healthProgress{static_cast<float>(GetHealth()) / static_cast<float>(m_MaxHealth)};
    m_BarWidget.SetProgress(healthProgress);
}

void BossEnemy::Draw() const
{
    glPushMatrix();

    glTranslatef(GetPosition().x, GetPosition().y, 0.f);
    glScalef(1.f / g_TileSize, 1.f / g_TileSize, 1.f);

    bool flipH{m_Velocity.x > 0.f};
    if (m_State == State::talking)
    {
        flipH = false;
    }

    glScalef(flipH ? -1.f : 1.f, 1.f, 1.f);
    glTranslatef(m_SourceRect.width * -0.5f, m_SourceRect.height * -0.5f, 0.f);

    GetSpriteSheet().Draw(Vector2f{}, m_SourceRect);

    glPopMatrix();
}

void BossEnemy::DrawGUI(const Rectf &viewport) const
{
    if (GetHealth() > 0)
    {
        const Rectf healthBar{utils::RectWithCenter(viewport.width * 0.5f, 100.f, viewport.width * 0.7f, 50.f)};
        utils::SetColor(Color4f(47.f / 255.f, 46.f / 255.f, 66.f / 255.f, 1.f));
        utils::FillRect(healthBar);

        const Rectf labelDest{healthBar.left, healthBar.bottom, m_BossLabelSourceRect.width * 2.f,
                              m_BossLabelSourceRect.height * 2.f};
        GetSpriteSheet().Draw(labelDest, m_BossLabelSourceRect);

        const Rectf barRegion{utils::SplitRectHorizontally(healthBar, 0.15f)[1]};
        m_BarWidget.Draw(barRegion.PadPerc(0.35f));
    }
}

void BossEnemy::StartAttacking(Player &player, Game &game)
{
    m_pGame = &game;
    m_State = State::moving;
    m_pPlayer = &player;
}

bool BossEnemy::TakeDamage(int amount)
{
    SetHealth(GetHealth() - amount);
    if (GetHealth() <= 0 && (m_State == State::moving || m_State == State::crushing))
    {
        assert(m_pGame && "Game not set");
        m_pGame->GetMusicManager().SwitchTrack(MusicManager::Track::none);

        m_pGame->GetDialogManager()->QueueMessage({"!!!", "I'll remember this!"});
        m_State = State::fleeing;
    }

    // despawn is handled by the boss itself for death dialog
    return false;
}

void BossEnemy::UpdateAnimations(float delta)
{
    m_AnimTimer += delta;
    if (m_AnimTimer > m_SecondsPerFrame)
    {
        m_AnimTimer = 0.f;
        ++m_AnimFrame;
    }
    CalcSourceRect(m_Velocity.y > 0.f);
}

void BossEnemy::CalcSourceRect(bool isJumping)
{
    if (isJumping)
    {
        m_SourceRect = Rectf(248.f, 224.f, m_PixelsWidth, m_PixelsHeight);
    }
    else if (m_State == State::talking)
    {
        m_SourceRect = Rectf(87.f, 274.f, m_PixelsWidth, m_PixelsHeight);
    }
    else if (m_State == State::moving)
    {
        m_AnimFrame = m_AnimFrame % 3;
        if (m_AnimFrame == 0)
        {
            m_SourceRect = Rectf(9.f, 228.f, m_PixelsWidth, m_PixelsHeight);
        }
        else if (m_AnimFrame == 1)
        {
            m_SourceRect = Rectf(89.f, 320.f, m_PixelsWidth, m_PixelsHeight);
        }
        else
        {
            m_SourceRect = Rectf(8.f, 320.f, m_PixelsWidth, m_PixelsHeight);
        }
    }
    else if (m_State == State::crushing)
    {
        m_AnimFrame = m_AnimFrame % 2;
        if (m_AnimFrame == 0)
        {
            m_SourceRect = Rectf(170.f, 327.f, m_PixelsWidth, m_PixelsHeight);
        }
        else if (m_AnimFrame == 1)
        {
            m_SourceRect = Rectf(248.f, 327.f, m_PixelsWidth, m_PixelsHeight);
        }
    }
}
