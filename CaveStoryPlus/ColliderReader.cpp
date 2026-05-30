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

    std::ifstream stream{m_FilePath};
    if (stream)
    {
        // https://en.cppreference.com/cpp/string/basic_string/getline

        PolygonCollider next{};
        for (std::string line; std::getline(stream, line);)
        {
            if (line.find("[PolygonCollider]") != std::string::npos)
            {
                colliders.emplace_back(ReadSingle(stream));
            }
        }
    }
    else
    {
        std::cerr << "Could not read colliders from: " << m_FilePath << std::endl;
    }

    return colliders.size() - startCount;
}

PolygonCollider ColliderReader::ReadSingle(std::ifstream &stream)
{
    PolygonCollider col{};
    // https://en.cppreference.com/cpp/string/basic_string/getline

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
