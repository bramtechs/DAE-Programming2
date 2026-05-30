#pragma once
#include "Texture.h"

class SpriteSheetManager final
{
  public:
    SpriteSheetManager();
    ~SpriteSheetManager();

    SpriteSheetManager(const SpriteSheetManager &) = delete;
    SpriteSheetManager &operator=(const SpriteSheetManager &) = delete;

    SpriteSheetManager(SpriteSheetManager &&) = delete;
    SpriteSheetManager &operator=(SpriteSheetManager &&) = delete;

    const Texture &GetEnemiesTexture() const;
    const Texture &GetInteractablesTexture() const;

  private:
    Texture *m_pEnemiesTexture;
    Texture *m_pInteractablesTexture;
};
