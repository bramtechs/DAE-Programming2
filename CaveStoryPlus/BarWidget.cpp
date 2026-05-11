#include "BarWidget.h"
#include "utils.h"

BarWidget::BarWidget(Color4f bgColor, Color4f fgColor) : m_BgColor(std::move(bgColor)), m_FgColor(std::move(fgColor))
{
}

void BarWidget::SetProgress(float progress)
{
    m_Progress = progress;
}

void BarWidget::Draw(const Rectf &region) const
{
    utils::SetColor(m_BgColor);
    utils::FillRect(region);

    Rectf filledRegion{region};
    filledRegion.width *= m_Progress;
    utils::SetColor(m_FgColor);
    utils::FillRect(filledRegion);
}
