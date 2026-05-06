#include "pch.h"
#include "PlayerGUI.h"
#include "Game.h"
#include "utils.h"

const Rectf PlayerGUI::m_LvlLabelTextureSource{163.f, 163.f, 24.f, 13.f};

PlayerGUI::PlayerGUI(const Player &player) : m_Player(player), m_pTexture(new Texture("TextBox.png"))
{
}

PlayerGUI::~PlayerGUI()
{
    delete m_pTexture;
}

void PlayerGUI::Draw() const
{
    const float padding{40.f};
    DrawHUD(Rectf{padding, g_ScreenHeight - padding - 300, 300, 100});
}

void PlayerGUI::DrawHUD(const Rectf &region) const
{
    utils::SetColor(Color4f{1.f, 0.f, 0.f, 1.f});
    utils::DrawRect(region);

    Rectf row{region};
    row.height = row.height * 0.5f * 0.5f;

    Rectf col{row};
    col.width /= 3;

    m_pTexture->Draw(utils::CalcCoverRegion(col, m_LvlLabelTextureSource), m_LvlLabelTextureSource);

    col.left += col.width;
    m_LevelLabel.Draw(col);
}
