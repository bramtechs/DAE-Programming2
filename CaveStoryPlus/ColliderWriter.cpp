#include "pch.h"
#include "PolygonCollider.h"
#include "ColliderWriter.h"

#include <iostream>

ColliderWriter::ColliderWriter(const std::string& colliderFilePath)
    : m_Stream(colliderFilePath), m_FilePath(colliderFilePath)
{
}

ColliderWriter::~ColliderWriter()
{
    std::cout << "Wrote colliders to: " << m_FilePath << std::endl;
}

void ColliderWriter::Serialize(const PolygonCollider& collider)
{
    m_Stream << "[PolygonCollider]\n";

    const std::vector<Vector2f>& colliders{ collider.GetPolygon() };
    for (int i{}; i < colliders.size(); ++i)
    {
        m_Stream << colliders[i].x << ";" << colliders[i].y << '\n';
    }

    m_Stream << '\n';
}
