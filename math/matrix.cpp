#include "matrix.h"

Transform2D::Transform2D()
    : Transform2D(0.0f,0.0f,1.0f,1.0f,0.0f)
{

}

Transform2D::Transform2D(float x, float y, float sx, float sy, float r)\
{
    mTranslation._x = x;
    mTranslation._y = y;

    mScale.m[0][0] = sx;
    mScale.m[0][1] = 0;
    mScale.m[1][0] = 0;
    mScale.m[1][1] = sy;

    mRotate.m[0][0] = std::cos(r);
    mRotate.m[0][1] = std::sin(r);
    mRotate.m[1][0] = -std::sin(r);
    mRotate.m[1][1] = std::cos(r);
}
