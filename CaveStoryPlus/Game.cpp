#include "pch.h"
#include "Game.h"
#include "Texture.h"
#include "Level.h"
#include "Player.h"
#include "Camera.h"

Game::Game(const Window& window)
	:BaseGame{ window }, m_Camera{ GetViewPort() }, m_pActiveLevel{}, m_pPlayer{}
{
	Initialize();

	m_Camera.SetCenter(m_pPlayer->GetCameraFocusPos());
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
	delete m_pActiveLevel;
	delete m_pPlayer;
}

void Game::Update(float elapsedSec)
{
	if (m_IsDebugging)
	{
		m_Camera.MoveWithKeyboard(elapsedSec);
		m_pActiveLevel->UpdateDebug(elapsedSec, m_Camera);
	}
	else
	{
		m_Camera.MoveTowards(m_pPlayer->GetCameraFocusPos(), elapsedSec);
		m_pActiveLevel->Update(elapsedSec);
	}
}

void Game::Draw() const
{
	m_Camera.Begin();

	ClearBackground();
	m_pActiveLevel->Draw();
	m_pPlayer->Draw();

	if (m_IsDebugging)
	{
		m_pActiveLevel->DrawDebug();
		m_pActiveLevel->DrawDebugGUI();
	}

	m_Camera.End();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;

	if (e.keysym.sym == SDLK_F3)
	{
		m_IsDebugging = !m_IsDebugging;
	}

}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}

}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
