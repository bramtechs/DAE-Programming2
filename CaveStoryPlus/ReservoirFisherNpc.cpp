#include "pch.h"
#include "ReservoirFisherNpc.h"

Rectf ReservoirFisherNpc::m_SourceRect{161.f, 340.f, 46.f, 48.f};

ReservoirFisherNpc::ReservoirFisherNpc(const Vector2f &pos) : DecorInteractable(Vector2f(pos.x, pos.y), m_SourceRect)
{
}
