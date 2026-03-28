#include "pch.h"
#include "Game.h"
#include "Texture.h"
#include "Level.h"
#include "Player.h"
#include "Camera.h"
#include "Editor.h"

Vector2f Game::m_LastMousePos{};

Game::Game(const Window& window)
    :BaseGame{ window }
    , m_Camera{ GetViewPort() }, m_pActiveLevel{}, m_pPlayer{}, m_pEditor{}
{
    Initialize();

    m_Camera.SetCenter(m_pPlayer->GetCameraFocusPosition());
}

Game::~Game()
{
    Cleanup();
}

void Game::Initialize()
{
    m_pActiveLevel = new Level("cave_first_map.png", "cave_first_map_outline.svg");
    m_pPlayer = new Player();
}

void Game::Cleanup()
{
    delete m_pEditor;
    delete m_pActiveLevel;
    delete m_pPlayer;
}

void Game::Update(float elapsedSec)
{
    if (m_pEditor)
    {
        m_Camera.MoveWithKeyboard(elapsedSec);
        m_pEditor->Update(m_Camera);
    }
    else
    {
        m_Camera.MoveTowards(m_pPlayer->GetCameraFocusPosition(), elapsedSec);
        m_pActiveLevel->Update(elapsedSec);
        if (m_pActiveLevel)
        {
            m_pPlayer->Update(elapsedSec, *m_pActiveLevel);
        }
    }
}

void Game::Draw() const
{
    m_Camera.Begin();

    ClearBackground();
    m_pActiveLevel->Draw();
    m_pPlayer->Draw();

    if (m_pEditor)
    {
        m_pEditor->Draw();
    }

    m_Camera.End();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
    //std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;

    if (e.keysym.sym == SDLK_F3)
    {
        if (m_pEditor)
        {
            delete m_pEditor;
            m_pEditor = nullptr;
        }
        else
        {
            m_pEditor = new Editor();
            m_pEditor->SetLevel(m_pActiveLevel);
        }
    }

    if (m_pPlayer)
    {
        m_pPlayer->HandleKeyDownEvent(e);
    }
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
    if (m_pPlayer)
    {
        m_pPlayer->HandleKeyUpEvent(e);
    }
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
    m_LastMousePos.x = static_cast<float>(e.x);
    m_LastMousePos.y = GetViewPort().height - static_cast<float>(e.y);
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
    if (m_pEditor)
    {
        m_pEditor->ProcessMouseDownEvent(e);
    }
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
    if (m_pEditor)
    {
        m_pEditor->ProcessMouseUpEvent(e);
    }
}

void Game::ClearBackground() const
{
    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
