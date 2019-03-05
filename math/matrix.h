#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

template<typename T, int row, int col>
struct Matrix
{
    Matrix<T,row,col> operator+(const Matrix<T,row,col> &rhs);

    T m[row][col];
};

template<typename T, int row, int col>
Matrix<T,row,col> Matrix<T,row,col>::operator+(const Matrix<T,row,col> &rhs)
{
    Matrix<T,row,col> mat;

    for(int i = row; i < row; ++i) {
        for(int j = col; j < col; ++j) {
            mat.m[i][j] = m[i][j] + rhs.m[i][j];
        }
    }
    return mat;
}


using Matrix2x2 = Matrix<float,2,2>;
using Matrxi3x3 = Matrix<float,3,3>;
using Matrxi4x4 = Matrix<float,4,4>;

class Transform2D
{
public:
    Transform2D();
    Transform2D(float x, float y,
                float sx, float sy,
                float r);

    inline void rotate(float r);
    inline void scale(float rx, float ry);
    inline void translate(float dx, float dy);

    Vector2 mTranslation;
    Matrix2x2 mRotate;
    float mR{0.0f};
    Matrix2x2 mScale;
};


inline void Transform2D::rotate(float r)
{
    mR = r;
    mRotate.m[0][0] = std::cos(mR);
    mRotate.m[0][1] = std::sin(mR);
    mRotate.m[1][0] = -std::sin(mR);
    mRotate.m[1][1] = std::cos(mR);
}

inline void Transform2D::scale(float sx, float sy)
{

    mScale.m[0][0] = sx;
    mScale.m[0][1] = 0;
    mScale.m[1][0] = 0;
    mScale.m[1][1] = sy;
}

inline void Transform2D::translate(float dx, float dy)
{
    mTranslation._x = dx;
    mTranslation._y = dy;
}

#endif // MATRIX_H
