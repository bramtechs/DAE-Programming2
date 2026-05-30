#include "pch.h"
#include "SpriteSheetManager.h"
#include "Texture.h"

SpriteSheetManager::SpriteSheetManager()
    : m_pEnemiesTexture(new Texture("enemies.png")), m_pInteractablesTexture(new Texture("interactables.png"))
{
}

SpriteSheetManager::~SpriteSheetManager()
{
    delete m_pInteractablesTexture;
    delete m_pEnemiesTexture;
}

const Texture &SpriteSheetManager::GetEnemiesTexture() const
{
    return *m_pEnemiesTexture;
}

const Texture &SpriteSheetManager::GetInteractablesTexture() const
{
    return *m_pInteractablesTexture;
}
