#pragma once

class Enemy
{
public:
	Enemy(const Vector2f& size);

	virtual ~Enemy() = default;

	virtual void Update(float delta) = 0;

	virtual void Draw() const = 0;

	virtual void DrawDebug() const;

	void SetPosition(Vector2f position);
	Vector2f GetPosition() const;

	Rectf GetRegion() const;

protected:
	Vector2f m_Position{};
	Vector2f m_Size{};
};

