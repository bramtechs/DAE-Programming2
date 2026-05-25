#pragma once

class Game;
class DialogEvent
{
  public:
    virtual ~DialogEvent() = default;

    virtual void Execute(Game &game) = 0;
};
