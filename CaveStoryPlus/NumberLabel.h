#pragma once
#include "structs.h"

class Texture;
class NumberLabel
{
  public:
    explicit NumberLabel(int value = 0);
    ~NumberLabel();

    NumberLabel(const NumberLabel &);
    NumberLabel &operator=(const NumberLabel &);
    
    NumberLabel(NumberLabel &&) = delete;
    NumberLabel &operator=(NumberLabel &&) = delete;

    void Draw(const Rectf &firstDigitRegion, bool drawPositiveSign = false) const;

    void Increment(int value = 1)
    {
        m_Value += value;
    }

    void SetValue(int value)
    {
        m_Value = value;
    }

    int GetValue() const
    {
        return m_Value;
    }

  private:
    int m_Value{};

    static Rectf GetDigitSource(int digit, bool positive);
    static Rectf GetSignSource(bool positive);

    const static Rectf m_FirstFrameSource;
    static Texture *m_pSpriteSheet;
    static int m_InstanceCount;
};
