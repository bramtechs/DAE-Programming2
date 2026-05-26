#include "pch.h"
#include "DialogMessage.h"
#include "TextManager.h"
#include "DialogEvent.h"
#include "structs.h"
#include "utils.h"

DialogMessage::DialogMessage(std::vector<std::string> &&lines, const TextManager &textManager)
    : m_pTextManager(&textManager)
{
    m_TextLines.reserve(lines.size());

    for (std::string &line : lines)
    {
        m_TextLines.emplace_back(std::move(line), m_pTextManager);
    }
}

DialogMessage::~DialogMessage()
{
    delete m_pEvent;
    m_pEvent = nullptr;
}

DialogMessage::DialogMessage(DialogMessage &&o) noexcept
    : m_pTextManager(o.m_pTextManager), m_TextLines(std::move(o.m_TextLines)), m_pEvent(o.m_pEvent), m_Timer(o.m_Timer),
      m_LinesVisible(o.m_LinesVisible)
{
    o.m_TextLines.clear();
    o.m_pEvent = nullptr;
}

DialogMessage &DialogMessage::operator=(DialogMessage &&o) noexcept
{
    if (this != &o)
    {
        delete m_pEvent;
        m_pTextManager = o.m_pTextManager;
        m_TextLines = std::move(o.m_TextLines);
        m_pEvent = o.m_pEvent;
        m_Timer = o.m_Timer;
        m_LinesVisible = o.m_LinesVisible;

        o.m_TextLines.clear();
        o.m_pEvent = nullptr;
    }

    return *this;
}

void DialogMessage::SetReadEvent(DialogEvent *pEvent)
{
    delete m_pEvent;
    m_pEvent = pEvent;
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
    utils::SetColor(Color4f{36.f / 255.f, 43.f / 255.f, 64.f / 255.f, 1.f});

    const Vector2f center{screenSize.x * 0.5f, screenSize.y * 0.2f};
    const Rectf region{utils::RectWithCenter(center, screenSize.x * 0.7f, screenSize.y * 0.3f)};
    utils::FillRect(region);

    utils::SetColor(Color4f{76.f / 255.f, 79.f / 255.f, 96.f / 255.f, 1.f});
    utils::DrawRect(region, 3.f);

    const Rectf contentRegion{region.PadPerc(0.2f)};
    float y{contentRegion.bottom + (contentRegion.height * 0.5f)};

    for (int lineNum{}; lineNum <= m_LinesVisible && lineNum < m_TextLines.size(); ++lineNum)
    {
        const TextLine &textLine{m_TextLines[lineNum]};
        const Vector2f bottomLeft{contentRegion.left, y};
        textLine.Draw(bottomLeft);
        y -= textLine.GetTextHeight();
    }
}

void DialogMessage::ExecuteReadEvent(Game &game)
{
    if (m_pEvent)
    {
        m_pEvent->Execute(game);
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
        if (m_LinesVisible + 1 < m_TextLines.size())
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
    if (m_TextLines.empty())
    {
        return true;
    }

    const size_t lastIndex{m_TextLines.size() - 1};
    if (m_LinesVisible < lastIndex)
    {
        // not at the last line yet
        return false;
    }

    return m_TextLines[lastIndex].IsDone();
}
