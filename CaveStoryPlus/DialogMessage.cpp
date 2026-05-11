#include "pch.h"
#include "DialogMessage.h"
#include "Texture.h"
#include "structs.h"
#include "utils.h"

DialogMessage::DialogMessage(std::string text, TextManager &textManager)
    : DialogMessage(std::initializer_list<std::string>{std::move(text)}, textManager)
{
}

DialogMessage::DialogMessage(std::initializer_list<std::string> lines, TextManager &textManager)
    : m_pTextManager(&textManager)
{
    m_pTextLines = new TextLine[std::distance(lines.begin(), lines.end())];

    for (const std::string &line : lines)
    {
        m_pTextLines[m_LineCount++] = TextLine{line, nullptr, 0};
    }
}

DialogMessage::~DialogMessage()
{
    for (int i{}; i < m_LineCount; ++i)
    {
        delete m_pTextLines[i].pTexture;
    }

    delete[] m_pTextLines;
}

void DialogMessage::AttachCallback(std::function<void(Game&)> &&cb)
{
    m_Callback = std::move(cb);
}

void DialogMessage::Update(float delta)
{
    if (IsDone())
        return;

    m_Timer += delta;
    if (m_Timer > m_SecondsPerChar)
    {
        m_Timer = 0.f;

        TextLine &currentLine{m_pTextLines[m_LinesVisible]};
        if (currentLine.IsDone())
            return;

        ++currentLine.charsVisible;
        currentLine.RebakeText(*m_pTextManager);
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
    float y{contentRegion.bottom + contentRegion.height * 0.5f};

    for (int lineNum{}; lineNum <= m_LinesVisible && lineNum < m_LineCount; ++lineNum)
    {
        const TextLine &textLine{m_pTextLines[lineNum]};
        if (textLine.pTexture)
        {
            const Vector2f origin{contentRegion.left, y};
            textLine.pTexture->Draw(origin);
            y -= textLine.pTexture->GetHeight();
        }
    }
}

void DialogMessage::ExecuteCallback(Game &game)
{
    if (m_Callback)
    {
        m_Callback(game);
    }
}

void DialogMessage::TextLine::RebakeText(TextManager &textManager)
{
    const int clamped{std::min(charsVisible, static_cast<int>(text.size()))};
    const std::string slice{text.substr(0, clamped)};

    delete pTexture;
    pTexture = textManager.BakeText(slice, 48);
}

void DialogMessage::Skip()
{
    if (IsDone())
        return;

    TextLine &line{m_pTextLines[m_LinesVisible]};
    if (line.IsDone())
    {
        if (m_LinesVisible + 1 < m_LineCount)
        {
            ++m_LinesVisible;
        }
    }
    else
    {
        line.charsVisible = static_cast<int>(line.text.size());
        line.RebakeText(*m_pTextManager);
    }
}

bool DialogMessage::IsDone() const
{
    if (m_LineCount == 0)
        return true;

    return m_LinesVisible >= m_LineCount - 1 && m_pTextLines[m_LineCount - 1].IsDone();
}
