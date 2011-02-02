#ifndef DEV_VEC2_H
#define DEV_VEC2_H

#include <Math/DevMath.h>

namespace dev
{
  class Vec2
  {
  public:
    union
    {
      struct
      {
        float x, y;
      };
      float v[2];
    };

    Vec2() 
    { 
      v[0] = 0;
      v[1] = 0;
    }

    Vec2(float x, float y) 
    { 
      v[0] = x;
      v[1] = y;
    };

    Vec2(const Vec2& vec)
    {
      v[0] = vec.x;
      v[1] = vec.y;
    }

    //operators
    inline bool operator == (const Vec2& vec) const 
    { 
      return (x == vec.x && y == vec.y); 
    }

    inline bool operator != (const Vec2& vec) const 
    {
      return (x != vec.x || y != vec.y); 
    }

    inline bool operator < (const Vec2& vec) const 
    { 
      return (x < vec.x && y < vec.y);
    }

    inline bool operator <= (const Vec2& vec) const 
    { 
      return (x <= vec.x && y <= vec.y); 
    }

    inline bool operator > (const Vec2& vec) const 
    { 
      return (x > vec.x && y > vec.y);
    }

    inline bool operator >= (const Vec2& vec) const 
    { 
      return (x >= vec.x && y >= vec.y); 
    }

    inline Vec2& operator *= (const float& scalar)
    {
      x *= scalar;
      y *= scalar;
      return *this;
    }

    inline const Vec2 operator * (const float& scalar) const
    {
      return Vec2(x * scalar, y * scalar);
    }

    inline float operator * (const Vec2& vec) const
    {
      return (x * vec.x + y * vec.y);
    }

    inline const Vec2 operator / (const float& scalar) const
    {
      float div = 1.0f / scalar;
      return Vec2(x * div, y * div);
    }

    inline Vec2& operator /= (const float& scalar)
    {
      float div = 1.0f / scalar;
      x *= div;
      y *= div;
      return *this;
    }

    inline const Vec2 operator + (const Vec2& vec) const
    {
        return Vec2(x + vec.x, y + vec.y);
    }

    inline Vec2& operator += (const Vec2& vec)
    {
        x += vec.x;
        y += vec.y;
        return *this;
    }

    inline const Vec2 operator + (const float& scalar) const
    {
      return Vec2(x + scalar, y + scalar);
    }

    inline Vec2& operator += (const float& scalar)
    {
      x += scalar;
      y += scalar;
      return *this;
    }

    inline const Vec2 operator - (const Vec2& vec) const
    {
      return Vec2(x - vec.x, y - vec.y);
    }

    inline Vec2& operator -= (const Vec2& vec)
    {
      x -= vec.x;
      y -= vec.y;
      return *this;
    }

    inline const Vec2 operator - (const float& scalar) const
    {
      return Vec2(x - scalar, y - scalar);
    }

    inline Vec2& operator -= (const float& scalar)
    {
      x -= scalar;
      y -= scalar;
      return *this;
    }

    inline const Vec2 operator - () const
    {
      return Vec2 (-x, -y);
    }

    inline float Length() const
    {
      return sqrtf(pow(x, 2) + pow(y, 2));
    }

    inline float Length2(void) const
    {
      return pow(x, 2) + pow(y, 2);
    }

    inline void operator = (const Vec2& vec)
    {
      x = vec.x;
      y = vec.y;
    }

    inline float Normalize()
    {
      float norm = Length();
      if (norm > 0.0)
      {
        float inv = 1.0f / norm;
        x *= inv;
        y *= inv;
      }
      return norm;
    }
  };
}

#endif