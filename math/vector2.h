#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

/*!
  Vector2
  定义：
    有大小、有方向的线段。
  性质：
    大小：线段的长度，即向量的模。 r = sqrt(x^2 + y^2)
    方向：...
  零向量
  单位向量
  负向量

  线性运算：
    v1 + v2
    scalar * v
  数量积：
    v .* v
  向量积：
    v * v


  二维图形变换：
    平移、比例、旋转、坐标变换
*/

const float PI = 3.1415926f;

struct Vector2
{
public:
    Vector2();
    Vector2(float x, float y);
    Vector2(const Vector2 &rhs);

    inline Vector2 &operator=(const Vector2 &rhs);
    inline float magnitude() const;
    inline float length() const;
    inline float direction() const; // radius
    inline Vector2 operator-();
    inline static Vector2 zero();
    inline static Vector2 unit();
    inline Vector2 operator+(const Vector2 &rhs);
    inline Vector2 &operator+=(const Vector2 &rhs);
    inline Vector2 operator-(const Vector2 &rhs);
    inline Vector2 &operator-=(const Vector2 &rhs);
    inline Vector2 operator*(float scalar);
    inline Vector2 &operator*=(float scalar);
    inline friend Vector2 operator*(float scalar, const Vector2 &vec);
    inline Vector2 operator/(float scalar);
    inline Vector2 &operator/=(float scalar);
    inline float dot(const Vector2 &rhs);

    // Vector2 operator*(const Vector2 &rhs);
    // Vector2 operator*=(const Vector2 &rhs);

public:
    float _x;
    float _y;
};


inline Vector2 &Vector2::operator=(const Vector2 &rhs)
{
    _x = rhs._x;
    _y = rhs._y;

    return *this;
}

inline float Vector2::magnitude() const
{
    return std::sqrt(_x * _x + _y * _y);
}

inline float Vector2::length() const
{
    return magnitude();
}

inline float Vector2::direction() const
{
    if(_x != 0.0f)
        return std::atan(_y/_x);
    else {
        return _y >= 0.0f ? (PI / 2.0f) : (-PI/2);
    }
}

inline Vector2 Vector2::operator-()
{
    return Vector2{-_x, -_y};
}

inline Vector2 Vector2::zero()
{
    return Vector2{0.0f,0.0f};
}

inline Vector2 Vector2::unit()
{
    return Vector2{1.0f,1.0f};
}

inline Vector2 Vector2::operator+(const Vector2 &rhs)
{
    return Vector2{_x + rhs._x, _y + rhs._y};
}

inline Vector2 &Vector2::operator+=(const Vector2 &rhs)
{
    _x += rhs._x;
    _y += rhs._y;
    return *this;
}

inline Vector2 Vector2::operator-(const Vector2 &rhs)
{
    return Vector2{_x - rhs._x, _y - rhs._y};
}

inline Vector2 &Vector2::operator-=(const Vector2 &rhs)
{
    _x -= rhs._x;
    _y -= rhs._y;
    return *this;
}

inline Vector2 Vector2::operator*(float scalar)
{
    return Vector2{_x * scalar, _y * scalar};
}

inline Vector2 &Vector2::operator*=(float scalar)
{
    _x *= scalar;
    _y *= scalar;
    return *this;
}

inline Vector2 operator*(float scalar, const Vector2 &vec)
{
    return Vector2{scalar * vec._x, scalar * vec._y};
}

inline Vector2 Vector2::operator/(float scalar)
{
    if(scalar != 0.0f) {
        return Vector2{_x / scalar, _y * scalar};
    }
    return Vector2{0.0f,0.0f};
}

inline Vector2 &Vector2::operator/=(float scalar)
{
    if(scalar != 0.0f) {
        _x /= scalar;
        _y /= scalar;
    } else {
        _x = 0.0f;
        _y = 0.0f;
    }
    return *this;
}

inline float Vector2::dot(const Vector2 &rhs)
{
    return _x * rhs._x + _y + rhs._y;
}

#endif // VECTOR2_H
