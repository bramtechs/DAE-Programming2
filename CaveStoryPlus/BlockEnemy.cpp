#include "pch.h"
#include "BlockEnemy.h"
#include "Texture.h"

const Rectf BlockEnemy::m_TextureSource{193.f, 97.f, 32.f, 32.f};

BlockEnemy::BlockEnemy(const Vector2f &tilePos) : Enemy(Vector2f{1.f, 1.f})
{
    SetPosition(tilePos + Vector2f(0.5f, 0.5f)); // align to tile grid
}

void BlockEnemy::InteractWithPlayer(Player &player)
{
}

void BlockEnemy::Update(float delta)
{
}

void BlockEnemy::Draw() const
{
    GetSpriteSheet().Draw(GetRegion(), m_TextureSource);
}
