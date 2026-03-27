#pragma once
#include <vector>

class Camera;
class PolygonCollider;
class Level;

class Editor
{
public:
    explicit Editor();

    void HandleColliders(std::vector<PolygonCollider>& colliders);

    void SetLevel(Level* pLevel);
    
    void Update(Camera& camera);
    void Draw() const;
    void DrawGUI() const;

private:
    void DrawTileGrid() const;
    void DrawColliders() const;

    Vector2f m_CursorPos{};
    Level* m_pLevel{};
};

