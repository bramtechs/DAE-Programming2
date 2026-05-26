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
    Color4f m_BgColor{73.f / 255.f, 38.f / 255.f, 1.f / 255.f, 1.f};
    Color4f m_FgColor{254.f / 255.f, 254.f / 255.f, 92.f / 255.f, 1.f};
    float m_Progress{};
};
