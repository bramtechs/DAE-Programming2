#include "pch.h"
#include "DialogMessage.h"
#include "TextManager.h"
#include "structs.h"
#include "utils.h"

DialogMessage::DialogMessage(std::vector<std::string> &&lines, const TextManager &textManager)
    : m_TextManager(textManager)
{
    m_TextLines.reserve(lines.size());

    for (std::string &line : lines)
    {
        m_TextLines.emplace_back(std::move(line), m_TextManager);
    }
}

void DialogMessage::AttachCallback(std::function<void(Game &)> &&cb)
{
    m_Callback = std::move(cb);
}

void DialogMessage::Update(float delta)
{
    if (IsDone())
    {
        return;
    }

    m_Timer += delta;
    if (m_Timer > m_SecondsPerChar)
    {
        m_Timer = 0.f;

        TextLine &currentLine{m_TextLines[m_LinesVisible]};
        if (!currentLine.IsDone())
        {
            currentLine.AdvanceText();
        }
    }
}

void DialogMessage::Draw(const Vector2f &screenSize) const
{
    utils::SetColor(utils::ColorHex(0x242B40));

    const Vector2f center{screenSize.x * 0.5f, screenSize.y * 0.2f};
    const Rectf region{utils::RectWithCenter(center, screenSize.x * 0.7f, screenSize.y * 0.3f)};
    utils::FillRect(region);

    utils::SetColor(utils::ColorHex(0x4C4F60));
    utils::DrawRect(region, 3.f);

    const Rectf contentRegion{region.PadPerc(0.2f)};
    float y{contentRegion.bottom + (contentRegion.height * 0.5f)};

    for (int lineNum{}; lineNum <= m_LinesVisible && lineNum < m_LineCount; ++lineNum)
    {
        const TextLine &textLine{m_TextLines[lineNum]};
        const Vector2f bottomLeft{contentRegion.left, y};
        textLine.Draw(bottomLeft);
        y -= textLine.GetTextHeight();
    }
}

void DialogMessage::ExecuteCallback(Game &game)
{
    if (m_Callback)
    {
        m_Callback(game);
    }
}

void DialogMessage::Skip()
{
    if (IsDone())
    {
        return;
    }

    TextLine &line{m_TextLines[m_LinesVisible]};
    if (line.IsDone())
    {
        if (m_LinesVisible + 1 < m_LineCount)
        {
            ++m_LinesVisible;
        }
    }
    else
    {
        line.SkipText();
    }
}

bool DialogMessage::IsDone() const
{
    if (m_LineCount == 0)
    {
        return true;
    }

    return m_LinesVisible >= m_LineCount - 1 && m_TextLines[m_LineCount - 1].IsDone();
}
