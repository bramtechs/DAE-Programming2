/*
 * Copyright (c) 2026. Doomhowl Interactive - All Rights Reserved
 * Redistribution and use in source and binary forms, with or without modification are not permitted
 * without the prior written permission of Doomhowl Interactive.
 *
 * File created on: 24-04-2026
 */

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
