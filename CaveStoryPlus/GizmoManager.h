/*
 * Copyright (c) 2026. Doomhowl Interactive - All Rights Reserved
 * Redistribution and use in source and binary forms, with or without modification are not permitted
 * without the prior written permission of Doomhowl Interactive.
 *
 * File created on: 24-04-2026
 */

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
