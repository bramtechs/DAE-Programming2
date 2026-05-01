#include "LevelBuilder.h"
#include "BatEnemy.h"
#include "Door.h"
#include "Level.h"
#include "LifeCapsuleInteractable.h"
#include "pch.h"

Level *LevelBuilder::BuildCaveLevel()
{
    Level *pLevel{new Level("cave_first_map.png", "cave_first_map.txt", Vector2f(37.f, 33.f))};

    // enemies
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{10.5f, 17.5f}, Vector2f{10.5f, 22.5f}}));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{14.5f, 20.5f}, Vector2f{14.5f, 25.5f}}));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{18.5f, 14.5f}, Vector2f{18.5f, 10.5f}}));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{25.5f, 7.5f}, Vector2f{25.5f, 12.5f}}));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{24.5f, 7.5f}, Vector2f{24.5f, 12.5f}}, 0.f));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{34.5f, 10.5f}, Vector2f{34.5f, 5.5f}}));

    // interactables

    // 6x20 live capsule
    pLevel->SpawnInteractable(new LifeCapsuleInteractable(Vector2f{6.f, 20.f}));

    // 53x8 door
    pLevel->SpawnInteractable(new Door(Vector2f{40.f, 33.f}, &LevelBuilder::BuildHermitGunsmithLevel));

    pLevel->SpawnInteractable(new Door(Vector2f{53.f, 8.f}, &LevelBuilder::BuildHermitGunsmithLevel));

    return pLevel;
}

Level *LevelBuilder::BuildHermitGunsmithLevel()
{
    Level *pLevel{new Level("cave_hermit_gunsmith.png", "cave_hermit_gunsmith_txt", Vector2f(7.f, 6.f))};
    // pLevel->SpawnInteractable();
    return pLevel;
}
