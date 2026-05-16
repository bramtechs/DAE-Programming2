#pragma once
#include "Vector2f.h"
#include "structs.h"
#include <SDL.h>
#include <vector>

class PolygonCollider
{
  public:
    PolygonCollider() = default;
    explicit PolygonCollider(std::vector<Vector2f> vertices);
    explicit PolygonCollider(const Rectf &rectangle);

    void PickColor(int index);

    bool StartDragAround(const Vector2f &tileMousePos);
    void StopDragAround();

    void AddPoint(const Vector2f &point);
    void AddPoint(float x, float y);

    void AddPointAfter(int index);
    void DeletePoint(int index);

    void Update(const Vector2f &snappedTileMousePos);
    void Draw() const;
    void DrawHandles(const Vector2f &tileMousePos) const;

    enum class Signal
    {
        none,
        handled,
        destroy
    };

    Signal ProcessKeyDownEvent(const SDL_KeyboardEvent &e);

    bool Overlaps(const Circlef &circle) const;

    bool IsPointAbove(const Vector2f &point) const;

    const std::vector<Vector2f> &GetPolygon() const
    {
        return m_Vertices;
    }

  private:
    static constexpr float m_HandleRadius{0.5f};

    Rectf GetHandleOfPoint(int pointIndex) const;

    std::vector<Vector2f> m_Vertices{};
    Color4f m_Color{1.f, 0.f, 0.f, 0.5f};
    int m_HandleBeingDragged{-1};
};
