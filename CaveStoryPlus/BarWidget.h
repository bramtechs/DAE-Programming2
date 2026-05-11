#pragma once
#include "structs.h"
#include "utils.h"

class BarWidget
{
  public:
    explicit BarWidget(Color4f bgColor, Color4f fgColor);

    void SetProgress(float progress);

    void Draw(const Rectf &region) const;

  private:
    Color4f m_BgColor{utils::ColorHex(0x492601)};
    Color4f m_FgColor{utils::ColorHex(0xFEFE5C)};
    float m_Progress{};
};
