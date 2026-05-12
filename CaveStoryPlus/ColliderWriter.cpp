#include "ColliderWriter.h"
#include "PolygonCollider.h"
#include "pch.h"

#include <filesystem>
#include <iostream>

ColliderWriter::ColliderWriter(const std::string &colliderFilePath)
    : m_Stream(colliderFilePath), m_FilePath(colliderFilePath)
{
}

ColliderWriter::~ColliderWriter()
{
    std::error_code err{};
    std::filesystem::path fullPath{std::filesystem::canonical(std::filesystem::current_path() / m_FilePath, err)};
    if (err)
    {
        fullPath = m_FilePath;
    }
    std::cout << "Wrote colliders to: " << fullPath.string() << std::endl;
}

void ColliderWriter::Serialize(const PolygonCollider &collider)
{
    m_Stream << "[PolygonCollider]\n";

    const std::vector<Vector2f> &colliders{collider.GetPolygon()};
    for (int i{}; i < colliders.size(); ++i)
    {
        m_Stream << colliders[i].x << ";" << colliders[i].y << '\n';
    }

    m_Stream << '\n';
}
