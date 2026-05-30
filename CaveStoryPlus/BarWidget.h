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
    const Color4f m_BgColor;
    const Color4f m_FgColor;
    float m_Progress{};
};
