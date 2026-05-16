#pragma once
#include "Vector2f.h"
#include <string>

struct Window
{
    explicit Window(const std::string &title = "Title", float width = 320.0f, float height = 180.0f,
                    bool isVSyncOn = true);

    std::string title;
    float width;
    float height;
    bool isVSyncOn;
};

struct Rectf
{
    Rectf();
    explicit Rectf(float left, float bottom, float width, float height);

    Rectf PadPerc(float perc) const;

    Vector2f GetCenter() const;

    float left;
    float bottom;
    float width;
    float height;
};

struct Color4f
{
    constexpr Color4f() : r(), g(), b(), a()
    {
    }

    constexpr explicit Color4f(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
    {
    }

    float r;
    float g;
    float b;
    float a;
};

struct Circlef
{
    Circlef();
    explicit Circlef(const Vector2f &center, float radius);
    explicit Circlef(float centerX, float centerY, float radius);

    Vector2f center;
    float radius;
};

struct Ellipsef
{
    Ellipsef();
    explicit Ellipsef(const Vector2f &center, float radiusX, float radiusY);
    explicit Ellipsef(float centerX, float centerY, float radiusX, float radiusY);

    Vector2f center;
    float radiusX;
    float radiusY;
};
