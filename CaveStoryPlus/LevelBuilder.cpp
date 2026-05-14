#include "pch.h"
#include "LevelBuilder.h"
#include "BatEnemy.h"
#include "ChestInteractable.h"
#include "DecorInteractable.h"
#include "DoorInteractable.h"
#include "JumperEnemy.h"
#include "Level.h"
#include "LifeCapsuleInteractable.h"
#include "GunSmithNpcInteractable.h"
#include "SpikeInteractable.h"

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

    pLevel->SpawnEnemy(new JumperEnemy(Vector2f{33.5f, 4.5f}, *pLevel));
    pLevel->SpawnEnemy(new JumperEnemy(Vector2f{45.5f, 33.5f}, *pLevel));

    // interactables

    // 6x20 live capsule
    pLevel->SpawnInteractable(new LifeCapsuleInteractable(Vector2f{6.f, 20.f}));

    // 53x8 door
    pLevel->SpawnInteractable(new DoorInteractable(Vector2f{40.f, 33.f}, &LevelBuilder::BuildHermitGunsmithLevel));

    pLevel->SpawnInteractable(new DoorInteractable(Vector2f{53.f, 8.f}, &LevelBuilder::BuildHermitGunsmithLevel));

    // spikes
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{32.f, 33.f}, SpikeInteractable::Orientation::ceiling));
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{31.f, 30.f}, SpikeInteractable::Orientation::floor));
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{24.f, 30.f}, SpikeInteractable::Orientation::ceiling));
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{22.f, 25.f}, SpikeInteractable::Orientation::floor));
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{8.f, 21.f}, SpikeInteractable::Orientation::leftWall));
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{15.f, 15.f}, SpikeInteractable::Orientation::rightWall));
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{17.f, 14.f}, SpikeInteractable::Orientation::ceiling));
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{33.f, 12.f}, SpikeInteractable::Orientation::ceiling));

    return pLevel;
}

Level *LevelBuilder::BuildHermitGunsmithLevel()
{
    Level *pLevel{new Level("cave_hermit_gunsmith.png", "cave_hermit_gunsmith_txt", Vector2f(7.f, 6.f))};
    // pLevel->SpawnInteractable();

    pLevel->SpawnInteractable(new DoorInteractable(Vector2f{7.f, 6.f}, &LevelBuilder::BuildCaveLevel));
    pLevel->SpawnInteractable(new DecorInteractable(Vector2f{11.f, 6.f}, Rectf{496.f, 368.f, 48.f, 32.f}));
    pLevel->SpawnInteractable(new GunSmithNpcInteractable(Vector2f{10.f, 6.f}));
    pLevel->SpawnInteractable(new ChestInteractable(Vector2f{14.f, 6.f}));

    return pLevel;
}
