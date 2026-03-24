#include "pch.h"
#include "utils.h"
#include "PolygonCollider.h"

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

void PolygonCollider::Draw() const
{
    utils::SetColor(m_Color);
    utils::FillPolygon(m_Vertices);
    utils::SetColor(Color4f{ m_Color.r * 0.5f, m_Color.g * 0.5f, m_Color.b * 0.5f, 1.f });
    utils::DrawPolygon(m_Vertices, true, 0.3f);
}

void PolygonCollider::DrawVertices() const
{
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
