#pragma once
#include "Texture.h"

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

    void Draw() const;

  private:
    void DrawHUD(const Rectf &region) const;

    static Rectf m_LvlLabelTextureSource;

    const Player &m_Player;
    Texture *m_pTexture{};
};
