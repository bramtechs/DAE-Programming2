#pragma once
#include "DialogMessage.h"
#include "structs.h"

#include <SDL.h>
#include <queue>
#include <string>

class DialogManager
{
  public:
    explicit DialogManager(TextManager &textManager, Game& game);

    void Update(float delta);
    void Draw(const Vector2f &screenSize) const;

    bool IsDialogOpen() const;

    DialogMessage& QueueMessage(const std::string &text);
    DialogMessage& QueueMessage(std::initializer_list<std::string>&& lines);

    void HandleKeyInput(const SDL_KeyboardEvent &e);

  private:
    TextManager &m_TextManager;
    Game &m_Game;
    std::queue<DialogMessage> m_Messages{};
};
