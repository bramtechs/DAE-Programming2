#pragma once

class Game;
class DialogEvent
{
  public:
    virtual ~DialogEvent() = default;

    virtual void Execute(Game &game) = 0;
};

class BossEnemy;
class SpawnBossDialogEvent final : public DialogEvent
{
  public:
    void Execute(Game &game) override;

  private:
    BossEnemy *m_pBossEnemy{};
};
