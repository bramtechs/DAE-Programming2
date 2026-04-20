#pragma once
#include "MultiLineLabel.h"
#include "pch.h"
#include <string>
#include <vector>

class Camera;
class PolygonCollider;
class Level;
class Texture;
class Editor
{
  public:
    Editor();

    Editor(const Editor &o) = delete;
    Editor &operator=(const Editor &o) = delete;

    void SetLevel(Level *pLevel);

    void Update(Camera &camera);
    void Draw() const;
    void DrawGUI() const;

    void ProcessMouseDownEvent(const SDL_MouseButtonEvent &e);
    void ProcessMouseUpEvent(const SDL_MouseButtonEvent &e);

    void ProcessKeyDownEvent(const SDL_KeyboardEvent &e);

  private:
    void SaveColliders() const;

    void DrawTileGrid() const;
    void DrawColliders() const;

    MultiLineLabel m_HelpLabel;
    float m_GridScale{1.f};
    Vector2f m_CursorPos{};
    Level *m_pLevel{};
};
