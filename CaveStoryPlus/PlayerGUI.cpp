#include "pch.h"
#include "PlayerGUI.h"
#include "Game.h"
#include "Player.h"
#include "utils.h"

const Rectf PlayerGUI::m_LvlLabelTextureSource{163.f, 163.f, 24.f, 13.f};
const Rectf PlayerGUI::m_HeartTextureSource{0.f, 80.f, 16.f, 16.f};
const std::array<Rectf, 2> PlayerGUI::m_OxygenTextureSources{Rectf{225.f, 144.f, 63.f, 15.f},
                                                             Rectf{225.f, 160.f, 63.f, 15.f}};

const std::array<Rectf, 2> PlayerGUI::m_LevelupSources{Rectf{311.f, 162.f, 111.f, 21.f},
                                                       Rectf{311.f, 195.f, 111.f, 21.f}};

PlayerGUI::PlayerGUI(const Player &player) : m_Player(player), m_pTexture(new Texture("TextBox.png"))
{
}

PlayerGUI::~PlayerGUI()
{
    delete m_pTexture;
}

void PlayerGUI::UpdateTimers(float delta)
{
    m_AnimTimer += delta;
    m_ShowLevelUpTimer -= delta;
}

void PlayerGUI::UpdateValues()
{
    m_HealthLabel.SetValue(m_Player.GetHealth());
    m_HealthBar.SetProgress(m_Player.GetHealth() / static_cast<float>(m_Player.GetMaxHealth()));

    m_LevelLabel.SetValue(m_Player.GetLevel());
    m_LevelBar.SetProgress(m_Player.GetLevelProgress());

    m_OxygenLabel.SetValue(m_Player.GetOxygen());
}

void PlayerGUI::Draw(const Rectf &viewport) const
{
    const float padding{40.f};
    DrawHUD(Rectf{padding, g_ScreenHeight - padding - 100.f, 330, 60});

    if (!m_Player.HasMaximumOxygen())
    {
        const int frame{(std::fmod(m_AnimTimer, 1.f) < 0.5f) ? 0 : 1};
        const Rectf oxygenRect{viewport.width * 0.5f - 80.f, viewport.height * 0.7f,
                               m_OxygenTextureSources[frame].width * 2.f, m_OxygenTextureSources[frame].height * 2.f};
        m_pTexture->Draw(oxygenRect, m_OxygenTextureSources[frame]);

        const float digitSize{26.f};
        const Rectf digitRegion{oxygenRect.left + m_OxygenTextureSources[frame].width * 2.5f, oxygenRect.bottom,
                                digitSize, digitSize};
        m_OxygenLabel.Draw(digitRegion, false);
    }

    if (m_ShowLevelUpTimer > 0.f)
    {
        const int frame{(std::fmod(m_AnimTimer, 0.5f) < 0.25f) ? 0 : 1};
        const Rectf source{m_LevelupSources[frame]};
        const Rectf destRegion{utils::RectWithCenter(Vector2f{viewport.width * 0.5f, viewport.height * 0.6f},
                                                     Vector2f{source.width, source.height} * 2.f)};
        m_pTexture->Draw(destRegion, source);
    }
}

void PlayerGUI::DrawHUD(const Rectf &region) const
{
    const std::array<Rectf, 3> bottomRow{GetRowColumns(region, 0, 2)};
    m_pTexture->Draw(utils::CalcCoverRegion(bottomRow[0], m_HeartTextureSource), m_HeartTextureSource);
    m_HealthLabel.Draw(bottomRow[1]);
    m_HealthBar.Draw(bottomRow[2]);

    const std::array<Rectf, 3> topRow{GetRowColumns(region, 1, 2)};
    m_pTexture->Draw(utils::CalcCoverRegion(topRow[0], m_LvlLabelTextureSource), m_LvlLabelTextureSource);
    m_LevelLabel.Draw(topRow[1]);
    m_LevelBar.Draw(topRow[2]);
}

void PlayerGUI::OnLevelUp()
{
    m_ShowLevelUpTimer = 1.5f;
}

std::array<Rectf, 3> PlayerGUI::GetRowColumns(const Rectf &region, int row, int totalRows) const
{
    Rectf rowRegion{region};
    rowRegion.height /= totalRows;
    rowRegion.bottom += rowRegion.height * row;

    const std::array<Rectf, 2> halves{utils::SplitRectHorizontally(rowRegion, 0.4f)};
    const std::array<Rectf, 2> leftHalves{utils::SplitRectHorizontally(halves[0], 0.35f)};

    return {leftHalves[0], leftHalves[1], halves[1]};
}
