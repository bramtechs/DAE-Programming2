#include "pch.h"
#include "Editor.h"
#include "Level.h"
#include "utils.h"
#include "Camera.h"

#include <cmath>

Editor::Editor()
{
}

void Editor::Update(Camera& camera)
{
    int mouseX{};
    int mouseY{};
    SDL_GetMouseState(&mouseX, &mouseY);
    mouseY = static_cast<int>(camera.GetViewPort().height) - mouseY;
    m_CursorPos = camera.ScreenToWorldPos(Vector2f{ static_cast<float>(mouseX), static_cast<float>(mouseY) });

    char pText[64];
    sprintf_s(pText, std::size(pText), "%dx%d", static_cast<int>(m_CursorPos.x), static_cast<int>(m_CursorPos.y));
    SDL_SetWindowTitle(SDL_GL_GetCurrentWindow(), pText);

    std::vector<PolygonCollider>& colliders{ m_pLevel->GetColliders() };
    for (int i{}; i < colliders.size(); ++i)
    {
        const Vector2f snappedCursor{ m_CursorPos.Round() };
        colliders[i].Update(snappedCursor);
    }
}

void Editor::Draw() const
{
    DrawTileGrid();
    DrawColliders();
}

void Editor::DrawGUI() const
{
}

void Level::GetLevelSize(int& outWidth, int& outHeight) const
{
    outWidth = m_LevelCols;
    outHeight = m_LevelRows;
}

void Editor::DrawTileGrid() const
{
    int levelCols, levelRows;
    m_pLevel->GetLevelSize(levelCols, levelRows);

    utils::SetColor(Color4f{ 0.8f,0.8f,0.8f,1.f });
    for (int row{}; row < levelRows; ++row)
    {
        utils::DrawLine(0.f, static_cast<float>(row), static_cast<float>(levelCols), static_cast<float>(row), 0.1f);
    }

    for (int col{}; col < levelCols; ++col)
    {
        utils::DrawLine(static_cast<float>(col), 0.f, static_cast<float>(col), static_cast<float>(levelRows), 0.1f);
    }

    utils::SetColor(Color4f{ 1.f,1.f,0.f,1.f });

    const float cursorX{ std::floor(m_CursorPos.x) };
    const float cursorY{ std::floor(m_CursorPos.y) };
    utils::DrawRect(Vector2f{ cursorX, cursorY }, 1.f, 1.f, 0.1f);
}

void Editor::DrawColliders() const
{
    const std::vector<PolygonCollider>& colliders{ m_pLevel->GetColliders() };
    for (int i{}; i < colliders.size(); ++i)
    {
        colliders[i].Draw();
        colliders[i].DrawHandles(m_CursorPos);
    }
}

void Editor::SetLevel(Level* pLevel)
{
    m_pLevel = pLevel;
}

void Editor::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
    if (e.button == SDL_BUTTON_LEFT)
    {
        std::vector<PolygonCollider>& colliders{ m_pLevel->GetColliders() };
        for (int i{}; i < colliders.size(); ++i)
        {
            colliders[i].StartDragAround(m_CursorPos);
        }
    }
}

void Editor::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
    if (e.button == SDL_BUTTON_LEFT)
    {
        std::vector<PolygonCollider>& colliders{ m_pLevel->GetColliders() };
        for (int i{}; i < colliders.size(); ++i)
        {
            colliders[i].StopDragAround();
        }
    }
}
