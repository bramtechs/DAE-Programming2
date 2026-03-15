#pragma once

class Texture;
class Player
{
public:
	Player();
	~Player();

	void Draw() const;

	Vector2f GetCameraFocusPos() const;

private:
	constexpr static float m_CellSize{32.f};

	Texture* m_pSpriteSheet{};
	Vector2f m_Position{37.f, 33.f};
	Vector2f m_Velocity{};
};

