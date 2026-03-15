#pragma once
#include <string>
#include <vector>

class Texture;
class Level
{
public:
	Level(const std::string& fullTexturePath, const std::string& levelPath);
	~Level();

	void Draw() const;

private:
	void DrawTileGrid() const;

	Texture* m_pFullTexture{};
	std::vector<std::vector<Vector2f>> m_Colliders{};
	int m_LevelCols{};
	int m_LevelRows{};
};

