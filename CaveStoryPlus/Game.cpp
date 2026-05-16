#include "pch.h"

#include "Camera.h"
#include "DialogManager.h"
#include "Editor.h"
#include "Game.h"
#include "Level.h"
#include "LevelBuilder.h"
#include "Player.h"
#include "PlayerGUI.h"
#include "SDL_keycode.h"
#include "TextManager.h"

Vector2f Game::m_LastMousePos{};

Game::Game(const Window &window) : BaseGame(window), m_Camera(GetViewPort())
{
    Initialize();
}

Game::~Game()
{
    Cleanup();
}

void Game::Initialize()
{
    m_pTextManager = new TextManager();

    LevelBuilder levelBuilder{};
    m_pActiveLevel = levelBuilder.BuildCaveLevel();
    // m_pActiveLevel = levelBuilder.BuildHermitGunsmithLevel();
    m_pDialogManager = new DialogManager(*m_pTextManager, *this);
    m_pPlayer = new Player(*m_pDialogManager);
    m_pPlayer->SetPosition(m_pActiveLevel->GetSpawnPos());
    m_pPlayerGUI = new PlayerGUI(*m_pPlayer);

    m_Camera.SetCenter(m_pPlayer->GetCameraFocusPosition());
}

void Game::Cleanup()
{
    delete m_pEditor;
    delete m_pActiveLevel;
    delete m_pNextLevel;
    delete m_pDialogManager;
    delete m_pTextManager;
    delete m_pPlayerGUI;
    delete m_pPlayer;
}

void Game::Update(float elapsedSec)
{
    if (m_pNextLevel)
    {
        delete m_pActiveLevel;
        m_pActiveLevel = m_pNextLevel;
        m_pNextLevel = nullptr;
        m_pPlayer->SetPosition(m_pActiveLevel->GetSpawnPos());
        m_Camera.SetCenter(m_pPlayer->GetPosition()); // avoid camera lerp effect
    }

    if (m_pEditor)
    {
        m_Camera.MoveWithKeyboard(elapsedSec);
        m_pEditor->Update(m_Camera);
    }
    else
    {
        if (!m_pDialogManager->IsDialogOpen())
        {
            m_Camera.MoveTowards(m_pPlayer->GetCameraFocusPosition(), elapsedSec);
            m_pActiveLevel->Update(elapsedSec, *m_pPlayer);
            if (m_pActiveLevel)
            {
                m_pPlayer->Update(elapsedSec, *m_pActiveLevel);
                if (m_pActiveLevel)
                {
                    m_pActiveLevel->InteractWithInteractables(*m_pPlayer, *this, false);
                }
            }
        }
        m_pDialogManager->Update(elapsedSec);
    }

    if (m_pActiveLevel)
    {
        m_Camera.ClampInside(m_pActiveLevel->GetBounds());
    }

    m_pPlayerGUI->Update();
}

void Game::Draw() const
{
    m_Camera.Begin();

    ClearBackground();
    m_pActiveLevel->Draw();
    m_pPlayer->Draw();

    if (m_pEditor)
    {
        m_pActiveLevel->DrawDebug();
        m_pEditor->Draw();
    }

    m_Camera.End();

    m_pPlayerGUI->Draw();

    const Vector2f screenSize{GetViewPort().width, GetViewPort().height};
    m_pDialogManager->Draw(screenSize);

    if (m_pEditor)
    {
        m_pEditor->DrawGUI();
    }
}

void Game::SwitchLevel(Level *pLevel)
{
    // level switch is delayed to next frame
    m_pNextLevel = pLevel;
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent &e)
{
    // std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;

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

    if (m_pDialogManager->IsDialogOpen())
    {
        m_pDialogManager->HandleKeyInput(e);
    }
    else if (m_pPlayer && m_pActiveLevel)
    {
        if (e.keysym.sym == SDLK_s || e.keysym.sym == SDLK_DOWN || e.keysym.sym == SDLK_RETURN)
        {
            if (m_pActiveLevel)
            {
                m_pActiveLevel->InteractWithInteractables(*m_pPlayer, *this, true);
            }
        }
        m_pPlayer->HandleKeyDownEvent(e);
    }

    if (m_pEditor)
    {
        m_pEditor->ProcessKeyDownEvent(e);
    }
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent &e)
{
    if (m_pPlayer)
    {
        m_pPlayer->HandleKeyUpEvent(e);
    }
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent &e)
{
    m_LastMousePos.x = static_cast<float>(e.x);
    m_LastMousePos.y = GetViewPort().height - static_cast<float>(e.y);
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent &e)
{
    if (m_pEditor)
    {
        m_pEditor->ProcessMouseDownEvent(e);
    }
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent &e)
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
