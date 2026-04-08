#include "Game.h"
#include "Camera.h"
#include "Editor.h"
#include "Level.h"
#include "LevelBuilder.h"
#include "Player.h"
#include "SDL_keycode.h"
#include "Texture.h"
#include "pch.h"

Vector2f Game::m_LastMousePos{};

Game::Game(const Window &window) : BaseGame{window}, m_Camera{GetViewPort()}, m_pActiveLevel{}, m_pPlayer{}, m_pEditor{}
{
    Initialize();
}

Game::~Game()
{
    Cleanup();
}

void Game::Initialize()
{
    LevelBuilder levelBuilder{};
    m_pActiveLevel = levelBuilder.BuildCaveLevel();
    m_pPlayer = new Player();
    m_pPlayer->SetPosition(levelBuilder.GetSpawnPos());

    m_Camera.SetCenter(m_pPlayer->GetCameraFocusPosition());
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
        m_pActiveLevel->Update(elapsedSec, *m_pPlayer);
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

GameContext Game::GetContext() const
{
    GameContext ctx{};
    ctx.pLevel = m_pActiveLevel;
    ctx.pPlayer = m_pPlayer;
    return ctx;
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
    else if (e.keysym.sym == SDLK_w || e.keysym.sym == SDLK_RETURN)
    {
        if (m_pActiveLevel)
        {
            m_pActiveLevel->TriggerInteractables(GetContext());
        }
    }

    if (m_pPlayer)
    {
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
