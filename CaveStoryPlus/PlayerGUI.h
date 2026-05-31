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
    explicit PlayerGUI(const Player &player);
    ~PlayerGUI();

    PlayerGUI(const PlayerGUI &) = delete;
    PlayerGUI &operator=(const PlayerGUI &) = delete;
    PlayerGUI(PlayerGUI &&) = delete;
    PlayerGUI &operator=(PlayerGUI &&) = delete;

    void UpdateTimers(float delta);

    void UpdateValues();

    void Draw(const Rectf &viewport) const;

    void OnLevelUp();

  private:
    void DrawHUD(const Rectf &region) const;

    std::array<Rectf, 3> GetRowColumns(const Rectf &region, int row, int totalRows) const;

    const static Rectf m_LvlLabelTextureSource;
    const static Rectf m_HeartTextureSource;
    const static std::array<Rectf, 2> m_OxygenTextureSources;
    const static std::array<Rectf, 2> m_LevelupSources;

    const Player &m_Player;
    const Texture *m_pTexture{};

    NumberLabel m_LevelLabel{};
    NumberLabel m_HealthLabel{};
    NumberLabel m_OxygenLabel{};

    BarWidget m_LevelBar{Color4f{73.f / 255.f, 38.f / 255.f, 1.f / 255.f, 1.f},
                         Color4f{254.f / 255.f, 254.f / 255.f, 92.f / 255.f, 1.f}};
    BarWidget m_HealthBar{Color4f{63.f / 255.f, 12.f / 255.f, 33.f / 255.f, 1.f},
                          Color4f{245.f / 255.f, 73.f / 255.f, 39.f / 255.f, 1.f}};

    float m_AnimTimer{};
    float m_LevelUpLabelShownTimer{};
};
