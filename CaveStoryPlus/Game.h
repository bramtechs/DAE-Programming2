#pragma once
#include "BaseGame.h"
#include "Camera.h"

constexpr float g_TileSize{ 32.f };
constexpr float g_TileCols{ 1280.f / 32.f };
constexpr float g_TileRows{ 720.f / 32.f };

class Level;
class Texture;
class Game : public BaseGame
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update(float elapsedSec) override;
	void Draw() const override;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e) override;
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e) override;
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e) override;
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) override;
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e) override;

private:
	Camera m_Camera;
	Level* m_pActiveLevel;

	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;
};