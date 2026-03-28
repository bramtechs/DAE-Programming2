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

    // @returns True if mouse consumed.
    bool StartDragAround(const Vector2f& tileMousePos);
    void StopDragAround();

    void Update(const Vector2f& snappedTileMousePos);
    void Draw() const;
    void DrawHandles(const Vector2f& tileMousePos) const;

private:
    void PickNextColor();

    Rectf GetHandleOfPoint(int pointIndex) const;

    static int m_ColliderCount;
    static constexpr float m_HandleRadius{0.5f};

    std::vector<Vector2f> m_Vertices{};
    Color4f m_Color{};
    int m_HandleBeingDragged{-1};
};

