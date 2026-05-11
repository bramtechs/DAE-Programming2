#pragma once
#include "TextManager.h"
#include "Vector2f.h"
#include <functional>
#include <initializer_list>
#include <string>
#include <vector>

class Game;
class DialogMessage
{
  public:
    explicit DialogMessage(std::string text, TextManager &textManager);
    explicit DialogMessage(std::initializer_list<std::string> lines, TextManager &textManager);
    ~DialogMessage();

    void AttachCallback(std::function<void(Game &)> &&cb);

    void Update(float delta);

    void Draw(const Vector2f &screenSize) const;

    void ExecuteCallback(Game& game);

    void Skip();

    bool IsDone() const;

  private:
    struct TextLine
    {
        std::string text{};
        Texture *pTexture{};
        int charsVisible{};

        void RebakeText(TextManager &textManager);
        bool IsDone() const
        {
            return charsVisible >= static_cast<int>(text.size());
        }
    };

    TextLine *m_pTextLines{};
    TextManager *m_pTextManager{};
    std::function<void(Game &)> m_Callback{};

    float m_Timer{};
    int m_LineCount{};
    int m_LinesVisible{};

    constexpr static float m_SecondsPerChar{0.05f};
};
