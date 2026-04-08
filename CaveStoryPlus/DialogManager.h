#pragma once
#include "DialogMessage.h"
#include "structs.h"

#include <SDL.h>
#include <queue>
#include <string>

class DialogManager
{
  public:
    DialogManager(TextManager &textManager);

    void Update(float delta);
    void Draw(const Vector2f &screenSize) const;

    bool IsDialogOpen() const;

    void QueueMessage(const std::string &text);
    void QueueMessage(std::initializer_list<std::string> lines);

    void HandleKeyInput(const SDL_KeyboardEvent &e);

  private:
    TextManager &m_TextManager;
    std::queue<DialogMessage> m_Messages{};
};
