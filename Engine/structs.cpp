#include "structs.h"
#include "base.h"

//-----------------------------------------------------------------
// Window Constructors
//-----------------------------------------------------------------
Window::Window(const std::string &title, float width, float height, bool isVSyncOn)
    : title{title}, width{width}, height{height}, isVSyncOn{isVSyncOn}
{
}

//-----------------------------------------------------------------
// Rectf Constructors
//-----------------------------------------------------------------
Rectf::Rectf() : Rectf{0.0f, 0.0f, 0.0f, 0.0f}
{
}

Rectf::Rectf(float left, float bottom, float width, float height)
    : left{left}, bottom{bottom}, width{width}, height{height}
{
}

Rectf Rectf::PadPerc(float perc) const
{
    const float least{std::min(width, height)};
    const float pad{least * perc};
    return Rectf(left + pad * 0.5f, bottom + pad * 0.5f, width - pad, height - pad);
}

//-----------------------------------------------------------------
// Circlef Constructors
//-----------------------------------------------------------------
Circlef::Circlef() : Circlef{0.0f, 0.0f, 0.0f}
{
}

Circlef::Circlef(float centerX, float centerY, float radius) : Circlef{Vector2f{centerX, centerY}, radius}
{
}

Circlef::Circlef(const Vector2f &center, float radius) : center{center}, radius{radius}
{
}

//-----------------------------------------------------------------
// Ellipsef Constructors
//-----------------------------------------------------------------
Ellipsef::Ellipsef() : Ellipsef{0.0f, 0.0f, 0.0f, 0.0f}
{
}

Ellipsef::Ellipsef(const Vector2f &center, float radiusX, float radiusY)
    : center{center}, radiusX{radiusX}, radiusY{radiusY}
{
}

Ellipsef::Ellipsef(float centerX, float centerY, float radiusX, float radiusY)
    : Ellipsef{Vector2f{centerX, centerY}, radiusX, radiusY}
{
}
