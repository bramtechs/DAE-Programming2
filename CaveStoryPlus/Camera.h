#pragma once
#include "Vector2f.h"

class Camera
{
public:
	Camera(const Rectf& viewPort);

	void Begin() const;

	void End() const;

	void SetCenter(const Vector2f& pos);

	void MoveWithKeyboard(float delta);
	void MoveTowards(const Vector2f& pos, float delta);

	Vector2f ScreenToWorldPos(const Vector2f& screenPos) const;

	Rectf GetViewPort() const;

private:
	Vector2f m_Center;
	Rectf m_ViewPort;
	float m_Zoom;
	float m_MoveSpeed;
};

