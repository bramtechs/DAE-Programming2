#pragma once
#include <string>
#include <fstream>

class PolygonCollider;
class ColliderWriter
{
public:
    explicit ColliderWriter(const std::string& colliderFilePath);
    ~ColliderWriter();

    void Serialize(const PolygonCollider& collider);

private:
    std::ofstream m_Stream;
    std::string m_FilePath;
};

