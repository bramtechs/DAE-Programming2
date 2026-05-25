#include "DialogEvents.h"
#include "BossEnemy.h"
#include "Game.h"
#include "Level.h"

void SpawnBossDialogEvent::Execute(Game &game)
{
    m_pBossEnemy = new BossEnemy(Vector2f{5.f, 6.72f});
    game.GetActiveLevel()->SpawnEnemy(m_pBossEnemy);
}
