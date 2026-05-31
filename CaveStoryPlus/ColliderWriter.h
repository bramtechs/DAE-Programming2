#pragma once
#include <string>
#include <fstream>

class PolygonCollider;
class ColliderWriter
{
public:
    explicit ColliderWriter(const std::string& colliderFilePath);

    void Serialize(const PolygonCollider& collider);

private:
    std::ofstream m_Stream;
    const std::string m_FilePath;
};

