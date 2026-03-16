#pragma once
#include "utils.h"
#include "Vector2f.h"
#include "Level.h"

class Texture;
class Player
{
public:
	Player();
	~Player();

	void Update(float delta, const Level& level);
	void Draw() const;

	void SetPosition(const Vector2f& pos);
	void SetPosition(float left, float bottom);

	Vector2f GetPosition() const;

	Vector2f GetCameraFocusPosition() const;

private:
	bool RaycastAgainstLevel(const Vector2f& start, const Vector2f& end, const Level::Colliders& colliders, utils::HitInfo& outHitInfo) const;

	constexpr static float m_CellSize{32.f};

	Texture* m_pSpriteSheet{};
	Vector2f m_Position{37.f, 33.f};
	Vector2f m_Velocity{};
	float m_Gravity{9.81f};
};

