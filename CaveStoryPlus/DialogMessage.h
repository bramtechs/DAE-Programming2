#pragma once
#include "TextManager.h"
#include "Vector2f.h"
#include <initializer_list>
#include <string>
#include <vector>

class DialogMessage
{
  public:
    explicit DialogMessage(std::string text, TextManager &textManager);
    explicit DialogMessage(std::initializer_list<std::string> lines, TextManager &textManager);
    ~DialogMessage();

    void Update(float delta);

    void Draw(const Vector2f &screenSize) const;

    void Skip();

    bool IsDone() const;

  private:
    struct TextLine
    {
        std::string text{};
        Texture *pTexture{};
        int charsVisible{};

        void RebakeText(TextManager &textManager);
        bool IsDone() const { return charsVisible >= static_cast<int>(text.size()); }
    };

    TextLine *m_pTextLines{};
    int m_LineCount{};
    TextManager *m_pTextManager{};
    int m_LinesVisible{};
    float m_Timer{};

    constexpr static float m_SecondsPerChar{0.05f};
};
