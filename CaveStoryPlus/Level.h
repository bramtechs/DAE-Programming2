#pragma once
#include <string>
#include <vector>

class Camera;
class Texture;
class Level
{
public:
	Level(const std::string& fullTexturePath, const std::string& levelPath);
	~Level();

	void Update(float delta);
	void UpdateDebug(float delta, const Camera& camera);

	void Draw() const;

	void DrawDebug() const;
	void DrawDebugGUI() const;

private:
	void DrawTileGrid() const;

	Texture* m_pFullTexture{};
	std::vector<std::vector<Vector2f>> m_Colliders{};
	int m_LevelCols{};
	int m_LevelRows{};
	Vector2f m_CursorPos{};
};

