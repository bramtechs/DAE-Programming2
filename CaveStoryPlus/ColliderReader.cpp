#include "pch.h"
#include "ColliderReader.h"
#include "PolygonCollider.h"

#include <iostream>

ColliderReader::ColliderReader(const std::string& colliderFilePath)
    : m_FilePath(colliderFilePath), m_Stream(m_FilePath)
{
}

size_t ColliderReader::ReadAllInto(std::vector<PolygonCollider>& colliders)
{
    if (!m_Stream.good())
    {
        std::cerr << "Could not read colliders from: " << m_FilePath << std::endl;
        return 0;
    }

    const size_t startCount{colliders.size()};
    
    PolygonCollider next{};
    for (std::string line; std::getline(m_Stream, line);)
    {
        if (line.find("[PolygonCollider]") != std::string::npos)
        {
            PolygonCollider col{ ReadSingle() };
            col.PickColor(static_cast<int>(colliders.size()));
            colliders.emplace_back(std::move(col));
        }
    }

    return colliders.size() - startCount;
}

PolygonCollider ColliderReader::ReadSingle()
{
    PolygonCollider col{};

    for (std::string line; std::getline(m_Stream, line);)
    {
        const size_t seperatorPos{ line.find(';') };
        if (seperatorPos == std::string::npos)
        {
            break;
        }

        Vector2f point{};
        point.x = std::stof(line);
        point.y = std::stof(line.substr(seperatorPos+1));
        col.AddPoint(point);
    }

    return col;
}
