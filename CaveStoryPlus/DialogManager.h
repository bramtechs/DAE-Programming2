#pragma once
#include "DialogMessage.h"
#include "structs.h"

#include <SDL.h>
#include <queue>
#include <string>

class DialogManager final
{
  public:
    explicit DialogManager(const TextManager &textManager, Game &game);
    
    DialogManager(const DialogManager &) = delete;
    DialogManager &operator=(const DialogEvent &) = delete;
    DialogManager(DialogManager &&) noexcept = delete;
    DialogManager &operator=(DialogManager &&) noexcept = delete;

    void Update(float delta);
    void Draw(const Rectf &viewport) const;

    bool IsDialogOpen() const;

    DialogMessage &QueueMessage(std::vector<std::string> &&lines);

    void HandleKeyInput(const SDL_KeyboardEvent &e);

  private:
    const TextManager& m_TextManager;
    Game &m_Game;
    std::queue<DialogMessage> m_Messages{};
};
