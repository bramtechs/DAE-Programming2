#pragma once
#include "Vector2f.h"
#include <vector>

class PolygonCollider
{
public:
    explicit PolygonCollider();
    explicit PolygonCollider(std::vector<Vector2f> vertices);

    PolygonCollider(PolygonCollider&& o) noexcept;
    PolygonCollider(const PolygonCollider& o);

    PolygonCollider& operator=(PolygonCollider&& o) noexcept;
    PolygonCollider& operator=(const PolygonCollider& o);

    ~PolygonCollider();

    const std::vector<Vector2f>& GetPolygon() const
    {
        return m_Vertices;
    }

    void Draw() const;
    void DrawVertices() const;

private:
    void PickNextColor();

    static int m_ColliderCount;

    std::vector<Vector2f> m_Vertices{};
    Color4f m_Color{};
};

