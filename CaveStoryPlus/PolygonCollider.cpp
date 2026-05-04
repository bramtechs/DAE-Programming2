#include "pch.h"
#include "utils.h"
#include "PolygonCollider.h"
#include "Game.h"

PolygonCollider::PolygonCollider(std::vector<Vector2f> vertices)
	: m_Vertices(std::move(vertices))
{
}

bool PolygonCollider::StartDragAround(const Vector2f& tileMousePos)
{
	for (int i{}; i < m_Vertices.size(); ++i)
	{
		const Rectf handle{ GetHandleOfPoint(i) };
		if (utils::IsPointInRect(tileMousePos, handle))
		{
			m_HandleBeingDragged = i;
			return true;
		}
	}

	return false;
}

void PolygonCollider::StopDragAround()
{
	m_HandleBeingDragged = -1;
}

void PolygonCollider::AddPoint(const Vector2f& point)
{
	m_Vertices.emplace_back(point);
}

void PolygonCollider::AddPoint(float x, float y)
{
	m_Vertices.emplace_back(x, y);
}

void PolygonCollider::AddPointAfter(int index)
{
	const int endIndex{ (index + 1) % static_cast<int>(m_Vertices.size()) };
	const Vector2f start{ m_Vertices[index] };
	const Vector2f end{ m_Vertices[endIndex] };

	const Vector2f interp{ start.Interpolate(end, 0.5f) };
	m_Vertices.insert(std::next(m_Vertices.begin(), endIndex), interp);

	m_HandleBeingDragged = -1;
}

void PolygonCollider::DeletePoint(int index)
{
	if (m_Vertices.size() > 3)
	{
		m_Vertices.erase(std::next(m_Vertices.begin(), index));
		m_HandleBeingDragged = -1;
	}
}

void PolygonCollider::Update(const Vector2f& snappedTileMousePos)
{
	if (m_HandleBeingDragged >= 0)
	{
		m_Vertices[m_HandleBeingDragged] = snappedTileMousePos;
	}
}

void PolygonCollider::Draw() const
{
	utils::SetColor(m_Color);
	utils::FillPolygon(m_Vertices);
	utils::SetColor(Color4f{ m_Color.r * 0.5f, m_Color.g * 0.5f, m_Color.b * 0.5f, 1.f });
	utils::DrawPolygon(m_Vertices, true, 0.3f);
}

void PolygonCollider::DrawHandles(const Vector2f& tileMousePos) const
{
	for (int i{}; i < m_Vertices.size(); ++i)
	{
		const Rectf handle{ GetHandleOfPoint(i) };
		if (utils::IsPointInRect(tileMousePos, handle) || m_HandleBeingDragged == i)
		{
			utils::SetColor(Color4f{ 0.2f,1.0f,0.2f,1.f });
		}
		else
		{
			utils::SetColor(Color4f{ 0.2f,0.2f,0.2f,1.f });
		}

		utils::FillRect(handle);
	}
}

void PolygonCollider::PickColor(int index)
{
	const float alpha{ 0.5f };
	const Color4f pRainbow[]{
		Color4f{1.0f, 0.0f, 0.0f, alpha},
		Color4f{1.0f, 0.5f, 0.0f, alpha},
		Color4f{1.0f, 1.0f, 0.0f, alpha},
		Color4f{0.0f, 1.0f, 0.0f, alpha},
		Color4f{0.0f, 0.0f, 1.0f, alpha},
		Color4f{0.29f, 0.0f, 0.51f, alpha},
		Color4f{0.56f, 0.0f, 1.0f, alpha}
	};

	m_Color = pRainbow[index % static_cast<int>(sizeof(pRainbow) / sizeof(Color4f))];
}

Rectf PolygonCollider::GetHandleOfPoint(int pointIndex) const
{
	Rectf region{};
	if (pointIndex >= 0 && pointIndex < m_Vertices.size())
	{
		region = utils::RectWithCenter(m_Vertices[pointIndex], m_HandleRadius, m_HandleRadius);
	}
	return region;
}

PolygonCollider::Signal PolygonCollider::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	if (m_HandleBeingDragged >= 0)
	{
		if (e.keysym.sym == SDLK_i)
		{
			AddPointAfter(m_HandleBeingDragged);
			return Signal::handled;
		}
		if (e.keysym.sym == SDLK_x)
		{
			DeletePoint(m_HandleBeingDragged);
			return Signal::none;
		}
		if (e.keysym.sym == SDLK_DELETE)
		{
			return Signal::destroy;
		}
	}
	return Signal::none;
}
