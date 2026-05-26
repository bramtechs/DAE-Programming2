#pragma once
#include <string>
#include <fstream>

class PolygonCollider;
class ColliderWriter
{
public:
    explicit ColliderWriter(const std::string& colliderFilePath);

    ColliderWriter(const ColliderWriter &) = delete;
    ColliderWriter &operator=(const ColliderWriter &) = delete;

    ColliderWriter &operator=(ColliderWriter &&) = delete;
    ColliderWriter(ColliderWriter &&) = delete;

    void Serialize(const PolygonCollider& collider);

private:
    std::ofstream m_Stream;
    std::string m_FilePath;
};

