#pragma once
#include "structs.h"

#include <vector>

class GizmoManager
{
  public:
    struct LineGizmo
    {
        Vector2f start{};
        Vector2f end{};
        Color4f color{1.f, 0.f, 0.f, 1.f};
    };

    void FlushAndDraw();

    void QueueGizmo(const LineGizmo &gizmo);

  private:
    std::vector<LineGizmo> m_Gizmos{};
};
