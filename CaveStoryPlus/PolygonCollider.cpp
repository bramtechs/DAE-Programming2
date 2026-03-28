#include "pch.h"
#include "utils.h"
#include "PolygonCollider.h"
#include "Game.h"

int PolygonCollider::m_ColliderCount{};

PolygonCollider::PolygonCollider()
{
    PickNextColor();
    ++m_ColliderCount;
}

PolygonCollider::PolygonCollider(std::vector<Vector2f> vertices)
    : m_Vertices(std::move(vertices))
{
    PickNextColor();
    ++m_ColliderCount;
}

PolygonCollider::PolygonCollider(PolygonCollider&& o) noexcept
    : m_Vertices(std::move(o.m_Vertices)), m_Color(o.m_Color)
{
}

PolygonCollider::PolygonCollider(const PolygonCollider& o)
    : m_Vertices(o.m_Vertices), m_Color(o.m_Color)
{
    ++m_ColliderCount;
}

PolygonCollider& PolygonCollider::operator=(PolygonCollider&& o) noexcept
{
    if (this != &o)
    {
        m_Vertices = std::move(o.m_Vertices);
        m_Color = o.m_Color;
    }
    return *this;
}

PolygonCollider& PolygonCollider::operator=(const PolygonCollider& o)
{
    if (this != &o)
    {
        m_Vertices = o.m_Vertices;
        m_Color = o.m_Color;
    }
    return *this;
}

PolygonCollider::~PolygonCollider()
{
    --m_ColliderCount;
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
        if (utils::IsPointInRect(tileMousePos, handle))
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

void PolygonCollider::PickNextColor()
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

    m_Color = pRainbow[m_ColliderCount];
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
