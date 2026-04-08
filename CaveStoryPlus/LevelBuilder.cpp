#include "LevelBuilder.h"
#include "BatEnemy.h"
#include "Level.h"
#include "LifeCapsule.h"
#include "pch.h"

Level *LevelBuilder::BuildCaveLevel()
{
    Level *pLevel{new Level("cave_first_map.png", "cave_first_map.txt")};

    // enemies
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{10.5f, 17.5f}, Vector2f{10.5f, 22.5f}}));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{14.5f, 20.5f}, Vector2f{14.5f, 25.5f}}));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{18.5f, 14.5f}, Vector2f{18.5f, 10.5f}}));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{25.5f, 7.5f}, Vector2f{25.5f, 12.5f}}));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{24.5f, 7.5f}, Vector2f{24.5f, 12.5f}}, 0.f));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{34.5f, 10.5f}, Vector2f{34.5f, 5.5f}}));

    // interactables

    // 6x20 live up
    pLevel->SpawnInteractable(new LifeCapsule(Vector2f{6.f, 20.f}));

    // 54x8 door

    m_SpawnPos = Vector2f{37.f, 33.f};
    return pLevel;
}

Vector2f LevelBuilder::GetSpawnPos() const
{
    return m_SpawnPos;
}
