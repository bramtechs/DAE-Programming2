#include "DialogManager.h"
#include "DialogMessage.h"
#include "Game.h"
#include "pch.h"

#include <iostream>

DialogManager::DialogManager(TextManager &textManager, Game &game) : m_TextManager(textManager), m_Game(game)
{
}

DialogMessage &DialogManager::QueueMessage(const std::string &text)
{
    return m_Messages.emplace(text, m_TextManager);
}

DialogMessage &DialogManager::QueueMessage(std::initializer_list<std::string> &&lines)
{
    return m_Messages.emplace(lines, m_TextManager);
}

void DialogManager::Update(float delta)
{
    if (!m_Messages.empty())
    {
        DialogMessage &message{m_Messages.front()};
        message.Update(delta);
    }
}

void DialogManager::Draw(const Vector2f &screenSize) const
{
    if (!m_Messages.empty())
    {
        const DialogMessage &message{m_Messages.front()};
        message.Draw(screenSize);
    }
}

void DialogManager::HandleKeyInput(const SDL_KeyboardEvent &e)
{
    if (e.keysym.sym == SDLK_RETURN || e.keysym.sym == SDLK_x)
    {
        if (!m_Messages.empty())
        {
            DialogMessage &message{m_Messages.front()};
            if (message.IsDone())
            {
                message.ExecuteCallback(m_Game);
                m_Messages.pop();
            }
            else
            {
                message.Skip();
            }
        }
    }
}

bool DialogManager::IsDialogOpen() const
{
    return !m_Messages.empty();
}
