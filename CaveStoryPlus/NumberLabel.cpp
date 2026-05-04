#include "NumberLabel.h"
#include "Texture.h"
#include "utils.h"

#include <cstring>

const Rectf NumberLabel::m_FirstFrameSource{0.f, 0.f, 16.f, 16.f};
Texture *NumberLabel::m_pSpriteSheet{};
int NumberLabel::m_InstanceCount{};

NumberLabel::NumberLabel(int value) : m_Value(value)
{
    if (m_InstanceCount == 0)
    {
        m_pSpriteSheet = new Texture("digits.png");
    }

    ++m_InstanceCount;
}

NumberLabel::~NumberLabel()
{
    --m_InstanceCount;

    if (m_InstanceCount == 0)
    {
        delete m_pSpriteSheet;
        m_pSpriteSheet = nullptr;
    }
}

NumberLabel::NumberLabel(const NumberLabel &o) : m_Value(o.m_Value)
{
    ++m_InstanceCount;
}

NumberLabel &NumberLabel::operator=(const NumberLabel &o)
{
    if (this != &o)
    {
        m_Value = o.m_Value;
    }

    return *this;
}

void NumberLabel::Draw(const Rectf &firstDigitRegion, bool drawPositiveSign) const
{
    Rectf region{utils::CalcCoverRegion(firstDigitRegion, m_FirstFrameSource)};

    char pText[32];
    std::snprintf(pText, sizeof(pText), "%d", m_Value);
    bool isPositive{true};

    if (drawPositiveSign && m_Value < 0)
    {
        m_pSpriteSheet->Draw(region, GetSignSource(isPositive));
        region.left += region.width;
    }

    for (int i{}; i < std::strlen(pText); ++i)
    {
        if (pText[i] == '-')
        {
            isPositive = false;
            m_pSpriteSheet->Draw(region, GetSignSource(false));
        }
        else
        {
            const int digit{static_cast<int>(pText[i] - '0')};
            m_pSpriteSheet->Draw(region, GetDigitSource(digit, isPositive));
        }

        region.left += region.width;
    }
}

Rectf NumberLabel::GetDigitSource(int digit, bool positive)
{
    digit = utils::Clamp(digit, 0, 9);

    Rectf region{m_FirstFrameSource};
    if (!positive)
    {
        region.bottom += 16.f;
    }

    region.left += digit * region.width;
    return region;
}

Rectf NumberLabel::GetSignSource(bool positive)
{
    Rectf region{0.f, 32.f, 16.f, 16.f};
    if (!positive)
    {
        region.left += region.width;
    }
    return region;
}
