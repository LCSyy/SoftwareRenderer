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
    平移 -- 位置变换 -- 向量加减
    旋转 -- 方向变换 -- 矩阵运算
    缩放 -- 大小变换 -- 数乘
    a1
    a2 = a1 + da

    [x, y] = [x0 + dx, y0 + dy]
           = [r * cos(a2), r * sin(a2)]
           = [r * cos(a1 + da), r * sin(a1 * da)]
           = [r * cos(a1)cos(da) - r * sin(a1)sin(da), r * sin(a1)cos(da) + r * cos(a1)sin(da)]
           = [x0 * cos(da) - y0 * sin(da), y0 * cos(da) + x0 * sin(da)]
           = [x0, y0] * [cos(da) sin(da)]
                        [-sin(da) cos(da)]

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
    inline Vector2 operator-() const;
    inline Vector2 operator+(const Vector2 &rhs) const;
    inline Vector2 &operator+=(const Vector2 &rhs);
    inline Vector2 operator-(const Vector2 &rhs) const;
    inline Vector2 &operator-=(const Vector2 &rhs);
    inline Vector2 operator*(float scalar) const;
    inline Vector2 &operator*=(float scalar);
    inline friend Vector2 operator*(float scalar, const Vector2 &vec);
    inline Vector2 operator/(float scalar) const;
    inline Vector2 &operator/=(float scalar);

    inline float dotProduct(const Vector2 &rhs) const;
    inline Vector2 scale(float factor) const;
    inline Vector2 rotate(float radius) const;
    inline Vector2 unit() const;
    inline float radians() const;

    // Vector2 operator*(const Vector2 &rhs);
    // Vector2 operator*=(const Vector2 &rhs);

    inline static Vector2 zero();
    inline static Vector2 one();
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

inline Vector2 Vector2::operator-() const
{
    return Vector2{-_x, -_y};
}

inline Vector2 Vector2::operator+(const Vector2 &rhs) const
{
    return Vector2{_x + rhs._x, _y + rhs._y};
}

inline Vector2 &Vector2::operator+=(const Vector2 &rhs)
{
    _x += rhs._x;
    _y += rhs._y;
    return *this;
}

inline Vector2 Vector2::operator-(const Vector2 &rhs) const
{
    return Vector2{_x - rhs._x, _y - rhs._y};
}

inline Vector2 &Vector2::operator-=(const Vector2 &rhs)
{
    _x -= rhs._x;
    _y -= rhs._y;
    return *this;
}

inline Vector2 Vector2::operator*(float scalar) const
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

inline Vector2 Vector2::operator/(float scalar) const
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

inline float Vector2::dotProduct(const Vector2 &rhs) const
{
    return _x * rhs._x + _y + rhs._y;
}

inline Vector2 Vector2::scale(float factor) const
{
    return Vector2{*this * factor};
}

inline Vector2 Vector2::rotate(float radius) const
{
    return Vector2{_x * std::cos(radius) - _y * std::sin(radius), _y * std::cos(radius) + _x * std::sin(radius)};
}

inline Vector2 Vector2::unit() const
{
    float len = length();
    if(len > 0.0f) {
        return Vector2{_x/len, _y/len};
    }
    return zero();
}

float Vector2::radians() const
{
    if(_x != 0.0f) {
        return std::atan(_y/_x);
    }
    return 0.0f;
}

inline Vector2 Vector2::zero()
{
    return Vector2{0.0f,0.0f};
}

inline Vector2 Vector2::one()
{
    return Vector2{1.0f,1.0f};
}


#endif // VECTOR2_H
