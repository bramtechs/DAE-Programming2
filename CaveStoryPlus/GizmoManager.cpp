#include "pch.h"
#include "GizmoManager.h"
#include "utils.h"

void GizmoManager::FlushAndDraw()
{
    for (const LineGizmo &gizmo : m_Gizmos)
    {
        utils::SetColor(gizmo.color);
        utils::DrawLine(gizmo.start, gizmo.end, 0.2f);
    }

    m_Gizmos.clear();
}

void GizmoManager::QueueGizmo(const LineGizmo &gizmo)
{
    m_Gizmos.emplace_back(gizmo);
}
