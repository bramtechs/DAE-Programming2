#include "ColliderWriter.h"
#include "PolygonCollider.h"
#include "pch.h"

#include <iostream>

ColliderWriter::ColliderWriter(const std::string &colliderFilePath)
    : m_Stream(colliderFilePath), m_FilePath(colliderFilePath)
{
}

void ColliderWriter::Serialize(const PolygonCollider &collider)
{
    m_Stream << "[PolygonCollider]\n";

    const std::vector<Vector2f> &colliders{collider.GetPolygonVertices()};
    for (int i{}; i < colliders.size(); ++i)
    {
        m_Stream << colliders[i].x << ";" << colliders[i].y << '\n';
    }

    m_Stream << '\n';
}
