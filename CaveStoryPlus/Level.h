#pragma once
#include "PolygonCollider.h"
#include <string>
#include <vector>
#include <fstream>

class Editor;
class Camera;
class Texture;

class Level
{
public:
    Level(const std::string& fullTexturePath, const std::string& collidersPath);
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

    std::string GetCollidersFilePath() const;

private:
    void DrawTileGrid() const;
    void DrawColliders() const;

    Texture* m_pFullTexture{};
    std::string m_CollidersPath{};
    std::vector<PolygonCollider> m_Colliders{};
    int m_LevelCols{};
    int m_LevelRows{};
    Vector2f m_CursorPos{};
};

