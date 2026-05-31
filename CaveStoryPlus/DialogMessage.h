#pragma once
#include "Vector2f.h"
#include "TextLine.h"

#include <functional>
#include <string>
#include <vector>

class Game;
class TextManager;
class DialogEvent;
class DialogMessage
{
  public:
    explicit DialogMessage(std::vector<std::string> &&lines, const TextManager &textManager);
    ~DialogMessage();

    DialogMessage(const DialogMessage &) = delete;
    DialogMessage &operator=(const DialogMessage &) = delete;

    DialogMessage(DialogMessage &&o) noexcept;
    DialogMessage &operator=(DialogMessage &&o) noexcept;

    void SetReadEvent(DialogEvent *pEvent);

    void Update(float delta);

    void Draw(const Vector2f &screenSize) const;

    void ExecuteReadEvent(Game &game);

    void Skip();

    bool IsDone() const;

  private:
    const TextManager &m_TextManager;
    std::vector<TextLine> m_TextLines{};
    DialogEvent *m_pEvent{};

    float m_Timer{};
    size_t m_LinesVisible{};

    static const float m_SecondsPerChar;
};
