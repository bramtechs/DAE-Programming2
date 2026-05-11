#include "PlayerGUI.h"
#include "Game.h"
#include "Player.h"
#include "pch.h"
#include "utils.h"

const Rectf PlayerGUI::m_LvlLabelTextureSource{163.f, 163.f, 24.f, 13.f};
const Rectf PlayerGUI::m_HeartTextureSource{0.f, 80.f, 16.f, 16.f};

PlayerGUI::PlayerGUI(const Player &player) : m_Player(player), m_pTexture(new Texture("TextBox.png"))
{
}

PlayerGUI::~PlayerGUI()
{
    delete m_pTexture;
}

void PlayerGUI::Update()
{
    m_HealthLabel.SetValue(m_Player.GetHealth());
    m_HealthBar.SetProgress(m_Player.GetHealth() / static_cast<float>(m_Player.GetMaxHealth()));
}

void PlayerGUI::Draw() const
{
    const float padding{40.f};
    DrawHUD(Rectf{padding, g_ScreenHeight - padding - 100.f, 330, 60});
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

std::array<Rectf, 3> PlayerGUI::GetRowColumns(const Rectf &region, int row, int totalRows) const
{
    Rectf rowRegion{region};
    rowRegion.height /= totalRows;
    rowRegion.bottom += rowRegion.height * row;

    const std::pair<Rectf, Rectf> halves{utils::SplitRectHorizontally(rowRegion, 0.4f)};
    const std::pair<Rectf, Rectf> leftHalves{utils::SplitRectHorizontally(halves.first, 0.35f)};

    return {leftHalves.first, leftHalves.second, halves.second};
}
