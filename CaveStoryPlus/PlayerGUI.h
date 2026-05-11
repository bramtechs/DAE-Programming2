#pragma once
#include "BarWidget.h"
#include "NumberLabel.h"
#include "Texture.h"
#include "utils.h"

#include <array>

class Player;
class PlayerGUI
{
  public:
    PlayerGUI(const Player &player);
    ~PlayerGUI();
    PlayerGUI(const PlayerGUI &) = delete;
    PlayerGUI(PlayerGUI &&) = delete;
    PlayerGUI &operator=(const PlayerGUI &) = delete;
    PlayerGUI &operator=(PlayerGUI &&) = delete;

    void Update();

    void Draw() const;

  private:
    void DrawHUD(const Rectf &region) const;

    std::array<Rectf, 3> GetRowColumns(const Rectf &region, int row, int totalRows) const;

    const static Rectf m_LvlLabelTextureSource;
    const static Rectf m_HeartTextureSource;

    const Player &m_Player;
    Texture *m_pTexture{};
    NumberLabel m_LevelLabel{};
    NumberLabel m_HealthLabel{};

    BarWidget m_LevelBar{utils::ColorHex(0x492601), utils::ColorHex(0xFEFE5C)};
    BarWidget m_HealthBar{utils::ColorHex(0x3F0C21), utils::ColorHex(0xFF0201)};
};
