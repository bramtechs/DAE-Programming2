#pragma once
#include "Vector2f.h"
#include "TextLine.h"

#include <functional>
#include <string>
#include <vector>

class Game;
class TextManager;
class DialogMessage
{
  public:
    explicit DialogMessage(std::vector<std::string> &&lines, const TextManager &textManager);

    void AttachCallback(std::function<void(Game &)> &&cb);

    void Update(float delta);

    void Draw(const Vector2f &screenSize) const;

    void ExecuteCallback(Game &game);

    void Skip();

    bool IsDone() const;

  private:
    std::vector<TextLine> m_TextLines{};
    const TextManager &m_TextManager;
    std::function<void(Game &)> m_Callback{};

    float m_Timer{};
    int m_LineCount{};
    int m_LinesVisible{};

    constexpr static float m_SecondsPerChar{0.05f};
};
