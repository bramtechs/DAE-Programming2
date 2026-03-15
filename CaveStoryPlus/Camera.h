#pragma once
#include "Vector2f.h"

class Camera
{
public:
	void Begin(const Rectf& viewPort) const;

	void End() const;

	void MoveWithKeyboard(float delta);

private:
	Vector2f m_Center{};
	float m_Zoom{2.f};
};

