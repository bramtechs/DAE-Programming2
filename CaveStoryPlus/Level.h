#pragma once
#include "PolygonCollider.h"
#include <string>
#include <vector>

class Editor;
class Camera;
class Texture;

class Level
{
public:
    Level(const std::string& fullTexturePath, const std::string& levelPath);
    ~Level();

    void Update(float delta);
    void Draw() const;

    void GetLevelSize(int& outWidth, int& outHeight) const;

    const std::vector<PolygonCollider>& GetColliders() const
    {
        return m_Colliders;
    }

    std::vector<PolygonCollider>& GetColliders()
    {
        return m_Colliders;
    }

private:
    void DrawTileGrid() const;
    void DrawColliders() const;

    Texture* m_pFullTexture{};
    std::vector<PolygonCollider> m_Colliders{
        PolygonCollider{std::vector<Vector2f>{
            Vector2f{-336.f,33.f},
            Vector2f{42.f,33.f},
            Vector2f{42.f,29.f},
            Vector2f{31.f,29.f}
        }}
    };
    int m_LevelCols{};
    int m_LevelRows{};
    Vector2f m_CursorPos{};
};

