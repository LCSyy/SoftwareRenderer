#include "./vector.h"

Vector2::Vector2()
    : _x(0.0f)
    , _y(0.0f)
{

}

Vector2::Vector2(float x, float y)
    : _x(x)
    , _y(y)
{

}

Vector2::Vector2(const Vector2 &rhs)
    : _x(rhs._x)
    , _y(rhs._y)
{

}
