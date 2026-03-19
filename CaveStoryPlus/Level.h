#pragma once
#include <string>
#include <vector>

class Camera;
class Texture;
class Level
{
public:
	using Colliders = std::vector<std::vector<Vector2f>>;

	Level(const std::string& fullTexturePath, const std::string& levelPath);
	~Level();

	void Update(float delta);
	void UpdateDebug(float delta, const Camera& camera);

	void Draw() const;

	void DrawDebug() const;
	void DrawDebugGUI() const;

	const Colliders& GetColliders() const;

private:
	void DrawTileGrid() const;
	void DrawColliders() const;

	Texture* m_pFullTexture{};
	Colliders m_Colliders{
		std::vector<Vector2f>{
			Vector2f{-336.f,33.f},
			Vector2f{42.f,33.f},
			Vector2f{42.f,29.f},
			Vector2f{31.f,29.f}
		}
	};
	int m_LevelCols{};
	int m_LevelRows{};
	Vector2f m_CursorPos{};
};

