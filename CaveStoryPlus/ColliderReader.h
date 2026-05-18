#pragma once
#include <string>
#include <fstream>
#include <vector>

class PolygonCollider;
class ColliderReader
{
  public:
    explicit ColliderReader(const std::string &colliderFilePath);

    size_t ReadAllInto(std::vector<PolygonCollider> &colliders);

  private:
    PolygonCollider ReadSingle(std::ifstream &stream);

    std::string m_FilePath;
};
