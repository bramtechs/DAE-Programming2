#include "pch.h"
#include "ColliderReader.h"
#include "PolygonCollider.h"

#include <iostream>

ColliderReader::ColliderReader(const std::string &colliderFilePath) : m_FilePath(colliderFilePath)
{
}

size_t ColliderReader::ReadAllInto(std::vector<PolygonCollider> &colliders)
{
    const size_t startCount{colliders.size()};
    try
    {
        std::ifstream stream{};
        stream.exceptions(std::ios::badbit); // throw on IO errors
        stream.open(m_FilePath);

        PolygonCollider next{};
        for (std::string line; std::getline(stream, line);)
        {
            if (line.find("[PolygonCollider]") != std::string::npos)
            {
                PolygonCollider col{ReadSingle(stream)};
                col.PickColor(static_cast<int>(colliders.size()));
                colliders.emplace_back(std::move(col));
            }
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Could not read (some) colliders from: " << m_FilePath << "\n" << ex.what() << std::endl;
    }

    return colliders.size() - startCount;
}

PolygonCollider ColliderReader::ReadSingle(std::ifstream &stream)
{
    PolygonCollider col{};

    for (std::string line; std::getline(stream, line);)
    {
        const size_t seperatorPos{line.find(';')};
        if (seperatorPos == std::string::npos)
        {
            break;
        }

        Vector2f point{};
        point.x = std::stof(line);
        point.y = std::stof(line.substr(seperatorPos + 1));
        col.AddPoint(point);
    }

    return col;
}
