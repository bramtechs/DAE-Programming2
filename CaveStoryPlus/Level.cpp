#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "Game.h"
#include "utils.h"

#include <iostream>

Level::Level(const std::string& fullTexturePath, const std::string& levelPath)
{
	m_pFullTexture = new Texture(fullTexturePath);

	m_LevelCols = static_cast<int>(m_pFullTexture->GetWidth()) / 16;
	m_LevelRows = static_cast<int>(m_pFullTexture->GetHeight()) / 16;
}

Level::~Level()
{
	delete m_pFullTexture;
}

void Level::Update(float delta)
{

}

void Level::UpdateDebug(float delta, const Camera& camera)
{
	int mouseX{};
	int mouseY{};
	SDL_GetMouseState(&mouseX, &mouseY);
	mouseY = static_cast<int>(camera.GetViewPort().height) - mouseY;
	m_CursorPos = camera.ScreenToWorldPos(Vector2f{ static_cast<float>(mouseX), static_cast<float>(mouseY) });
	m_CursorPos.x = std::floor(m_CursorPos.x);
	m_CursorPos.y = std::floor(m_CursorPos.y);


	char pText[64];
	sprintf_s(pText, std::size(pText), "%dx%d", static_cast<int>(m_CursorPos.x), static_cast<int>(m_CursorPos.y));
	SDL_SetWindowTitle(SDL_GL_GetCurrentWindow(), pText);
}

void Level::Draw() const
{
	const float scaledWidth{ m_pFullTexture->GetWidth() / g_TileSize * 2.f };
	const float scaledHeight{ m_pFullTexture->GetHeight() / g_TileSize * 2.f };
	m_pFullTexture->Draw(Rectf{ 0.f, 0.f, scaledWidth, scaledHeight });
}

void Level::DrawDebug() const
{
	DrawTileGrid();
	DrawColliders();
}

void Level::DrawDebugGUI() const
{
}

void Level::DrawTileGrid() const
{
	utils::SetColor(Color4f{ 0.8f,0.8f,0.8f,1.f });
	for (int row{}; row < m_LevelRows; ++row)
	{
		utils::DrawLine(0.f, static_cast<float>(row), static_cast<float>(m_LevelCols), static_cast<float>(row), 0.1f);
	}

	for (int col{}; col < m_LevelCols; ++col)
	{
		utils::DrawLine(static_cast<float>(col), 0.f, static_cast<float>(col), static_cast<float>(m_LevelRows), 0.1f);
	}

	utils::SetColor(Color4f{ 1.f,1.f,0.f,1.f });
	utils::DrawRect(m_CursorPos, 1.f, 1.f, 0.1f);
}

void Level::DrawColliders() const
{
	for (int i{}; i < m_Colliders.size(); ++i)
	{
		m_Colliders[i].Draw();
	}
}
