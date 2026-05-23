#include "pch.h"
#include "LevelBuilder.h"
#include "BatEnemy.h"
#include "ChestInteractable.h"
#include "DecorInteractable.h"
#include "DoorInteractable.h"
#include "BlockEnemy.h"
#include "JumperEnemy.h"
#include "Player.h"
#include "PolarStar.h"
#include "Level.h"
#include "MimigaVillageNpc.h"
#include "PickupInteractable.h"
#include "LifeCapsuleInteractable.h"
#include "ReservoirFisherNpc.h"
#include "WaterInteractable.h"
#include "GunSmithNpcInteractable.h"
#include "SpikeInteractable.h"

#include <cassert>

LevelBuilder::LevelBuilder(const Player &player) : m_Player(player)
{
}

Level *LevelBuilder::BuildLevel(LevelBuilder::Type type) const
{
    switch (type)
    {
    case LevelBuilder::Type::cave:
        return BuildCaveLevel();
    case LevelBuilder::Type::hermitGunsmith:
        return BuildHermitGunsmithLevel();
    case LevelBuilder::Type::mimigaVillage:
        return BuildMimigaVillageLevel();
    case LevelBuilder::Type::mimigaReservoir:
        return BuildMimigaReservoirLevel();
    case LevelBuilder::Type::mimigaShack:
        return BuildMimigaShackLevel();
    }

    assert(0 && "Case not handled");
    return nullptr;
}

Level *LevelBuilder::BuildCaveLevel() const
{
    Level *pLevel{new Level("cave_first_map.png", "cave_first_map.txt", "First Cave", Vector2f(37.f, 33.f),
                            MusicManager::Track::cave)};

    // enemies
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{10.5f, 17.5f}, Vector2f{10.5f, 22.5f}}));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{14.5f, 20.5f}, Vector2f{14.5f, 25.5f}}));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{18.5f, 14.5f}, Vector2f{18.5f, 10.5f}}));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{25.5f, 7.5f}, Vector2f{25.5f, 12.5f}}));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{24.5f, 7.5f}, Vector2f{24.5f, 12.5f}}, 0.f));
    pLevel->SpawnEnemy(new BatEnemy(std::vector<Vector2f>{Vector2f{34.5f, 10.5f}, Vector2f{34.5f, 5.5f}}));

    pLevel->SpawnEnemy(new JumperEnemy(Vector2f{33.5f, 4.5f}, *pLevel));
    pLevel->SpawnEnemy(new JumperEnemy(Vector2f{45.5f, 33.5f}, *pLevel));

    pLevel->SpawnEnemy(new JumperEnemy(Vector2f{50.5f, 32.5f}, *pLevel));
    pLevel->SpawnEnemy(new JumperEnemy(Vector2f{53.5f, 33.5f}, *pLevel));

    pLevel->SpawnEnemy(new BlockEnemy(Vector2f{42.f, 33.f}));
    pLevel->SpawnEnemy(new BlockEnemy(Vector2f{47.f, 35.f}));
    pLevel->SpawnEnemy(new BlockEnemy(Vector2f{47.f, 34.f}));
    pLevel->SpawnEnemy(new BlockEnemy(Vector2f{47.f, 33.f}));

    // interactables

    // 6x20 live capsule
    if (m_Player.GetMaxHealth() == 3)
    {
        pLevel->SpawnInteractable(new LifeCapsuleInteractable(Vector2f{6.f, 20.f}));
    }

    // 53x8 door
    pLevel->SpawnInteractable(new DoorInteractable(Vector2f{53.f, 8.f}, LevelBuilder::Type::hermitGunsmith));
    pLevel->SpawnInteractable(new DoorInteractable(Vector2f{55.f, 35.f}, LevelBuilder::Type::mimigaVillage));

    // spikes
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{32.f, 33.f}, SpikeInteractable::Orientation::ceiling));
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{31.f, 30.f}, SpikeInteractable::Orientation::floor));
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{24.f, 30.f}, SpikeInteractable::Orientation::ceiling));
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{22.f, 25.f}, SpikeInteractable::Orientation::floor));
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{8.f, 21.f}, SpikeInteractable::Orientation::leftWall));
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{15.f, 15.f}, SpikeInteractable::Orientation::rightWall));
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{17.f, 14.f}, SpikeInteractable::Orientation::ceiling));
    pLevel->SpawnInteractable(new SpikeInteractable(Vector2f{33.f, 12.f}, SpikeInteractable::Orientation::ceiling));

    // water
    pLevel->SpawnInteractable(new WaterInteractable(Rectf{38.f, 3.f, 20.f, 3.f}));
    pLevel->SpawnInteractable(new WaterInteractable(Rectf{32.f, 3.f, 4.f, 2.f}));
    pLevel->SpawnInteractable(new WaterInteractable(Rectf{26.f, 6.f, 6.f, 1.f}));

    return pLevel;
}

Level *LevelBuilder::BuildHermitGunsmithLevel() const
{
    Level *pLevel{new Level("cave_hermit_gunsmith.png", "cave_hermit_gunsmith_txt", "Hermit Gunsmith",
                            Vector2f(7.f, 6.f), MusicManager::Track::cave)};
    // pLevel->SpawnInteractable();

    pLevel->SpawnInteractable(new DoorInteractable(Vector2f{7.f, 6.f}, LevelBuilder::Type::cave, Vector2f{53.f, 8.f}));
    pLevel->SpawnInteractable(new DecorInteractable(Vector2f{11.f, 6.f}, Rectf{496.f, 368.f, 48.f, 32.f}));
    pLevel->SpawnInteractable(new GunSmithNpcInteractable(Vector2f{10.f, 6.f}));

    ChestInteractable *pChest{new ChestInteractable(Vector2f{14.f, 6.f})};
    pChest->SetOpened(m_Player.IsHoldingWeapon<PolarStar>());
    pLevel->SpawnInteractable(pChest);

    return pLevel;
}

Level *LevelBuilder::BuildMimigaVillageLevel() const
{
    Level *pLevel{new Level("mimiga_village.png", "mimiga_village_map.txt", "Mimiga Village", Vector2f(8.f, 53.f),
                            MusicManager::Track::village)};

    pLevel->SpawnInteractable(new MimigaVillageNpc(Vector2f{10.f, 25.f}));

    pLevel->SpawnInteractable(new DoorInteractable(Vector2f{1.f, 21.f}, LevelBuilder::Type::mimigaReservoir));

    return pLevel;
}

Level *LevelBuilder::BuildMimigaReservoirLevel() const
{
    Level *pLevel{new Level("mimiga_village_reservoir.png", "mimiga_village_reservoir_map.txt", "Reservoir",
                            Vector2f{36.f, 5.f}, MusicManager::Track::village)};

    pLevel->SpawnInteractable(
        new DoorInteractable(Vector2f{36.f, 5.f}, LevelBuilder::Type::mimigaVillage, Vector2f{1.f, 21.f}));

    pLevel->SpawnInteractable(new PickupInteractable(Vector2f{5.f, 4.f}));
    pLevel->SpawnInteractable(new ReservoirFisherNpc(Vector2f{5.5f, 6.63f}));
    pLevel->SpawnInteractable(new WaterInteractable(Rectf{1.f, 1.f, 23.f, 5.5f}));

    return pLevel;
}

Level *LevelBuilder::BuildMimigaShackLevel() const
{
    Level *pLevel{new Level("mimiga_village_shack.png", "mimiga_village_shack_map.txt", "Shack", Vector2f{5.f, 6.f},
                            MusicManager::Track::none)};

    if (false)
    {
        pLevel->SpawnInteractable(new DoorInteractable(Vector2f{5.f, 6.f}, LevelBuilder::Type::mimigaVillage));
    }

    return pLevel;
}
