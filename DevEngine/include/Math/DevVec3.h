#ifndef DEV_VEC3_H
#define DEV_VEC3_H

#include <Math/DevVec2.h>

namespace dev
{
  class Vec3
  {
  public:
    union
    {
      struct
      {
        float x, y, z;
      };
      float v[3];
    };

    Vec3() 
    { 
      v[0] = 0;
      v[1] = 0;
      v[2] = 0;
    }

    Vec3(float x, float y, float z) 
    { 
      v[0] = x;
      v[1] = y;
      v[2] = z;
    };

    Vec3(const Vec2& vec, float z)
    {
      v[0] = vec.x;
      v[1] = vec.y;
      v[2] = z;
    }
    
    Vec3(const Vec3& vec)
    {
      v[0] = vec.x;
      v[1] = vec.y;
      v[2] = vec.z;
    }

    //operators
    inline bool operator == (const Vec3& vec) const 
    { 
      return (x == vec.x && y == vec.y && z == vec.z); 
    }

    inline bool operator != (const Vec3& vec) const 
    {
      return (x != vec.x || y != vec.y || z != vec.z); 
    }

    inline bool operator < (const Vec3& vec) const 
    { 
      return (x < vec.x && y < vec.y && z < vec.z);
    }

    inline bool operator <= (const Vec3& vec) const 
    { 
      return (x <= vec.x && y <= vec.y && z <= vec.z); 
    }

    inline bool operator > (const Vec3& vec) const 
    { 
      return (x > vec.x && y > vec.y && z > vec.z);
    }

    inline bool operator >= (const Vec3& vec) const 
    { 
      return (x >= vec.x && y >= vec.y && z >= vec.z); 
    }

    inline Vec3& operator ^= (const Vec3& vec)
    {
      x = y * vec.z - z * vec.y;
      y = z * vec.x - x * vec.z;
      z = x * vec.y - y * vec.x;
      return *this;
    }

    inline const Vec3 operator ^ (const Vec3& vec) const
    {
      return Vec3(y * vec.z - z * vec.y,
                  z * vec.x - x * vec.z,
                  x * vec.y - y * vec.x);
    }

    inline Vec3& operator *= (const float& scalar)
    {
      x *= scalar;
      y *= scalar;
      z *= scalar;
      return *this;
    }

    inline const Vec3 operator * (const float& scalar) const
    {
      return Vec3(x * scalar, y * scalar, z * scalar);
    }

    inline float operator * (const Vec3& vec) const
    {
      return (x * vec.x + y * vec.y + z * vec.z);
    }

    inline const Vec3 operator / (const float& scalar) const
    {
      return Vec3(x / scalar, y / scalar, z / scalar);
    }

    inline Vec3& operator /= (const float& scalar)
    {
      x /= scalar;
      y /= scalar;
      z /= scalar;
      return *this;
    }

    inline const Vec3 operator + (const Vec3& vec) const
    {
      return Vec3(x + vec.x, y + vec.y, z + vec.z);
    }

    inline Vec3& operator += (const Vec3& vec)
    {
      x += vec.x;
      y += vec.y;
      z += vec.z;
      return *this;
    }

    inline const Vec3 operator + (const float& scalar) const
    {
      return Vec3(x + scalar, y + scalar, z + scalar);
    }

    inline Vec3& operator += (const float& scalar)
    {
      x += scalar;
      y += scalar;
      z += scalar;
      return *this;
    }

    inline const Vec3 operator - (const Vec3& vec) const
    {
      return Vec3(x - vec.x, y - vec.y, z - vec.z);
    }

    inline Vec3& operator -= (const Vec3& vec)
    {
      x -= vec.x;
      y -= vec.y;
      z -= vec.z;
      return *this;
    }

    inline const Vec3 operator - (const float& scalar) const
    {
      return Vec3(x - scalar, y - scalar, z - scalar);
    }

    inline Vec3& operator -= (const float& scalar)
    {
      x -= scalar;
      y -= scalar;
      z -= scalar;
      return *this;
    }

    inline const Vec3 operator - () const
    {
      return Vec3 (-x, -y, -z);
    }

    inline float Length() const
    {
      return sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }

    inline float Length2(void) const
    {
      return pow(x, 2) + pow(y, 2) + pow(z, 2);
    }

    inline void operator = (const Vec3& vec)
    {
      x = vec.x;
      y = vec.y;
      z = vec.z;
    }

    inline float Normalize()
    {
      float norm = Length();
      if (norm > 0.0)
      {
        float inv = 1.0f / norm;
        x *= inv;
        y *= inv;
        z *= inv;
      }
      return norm;
    }
  };

  const Vec3 X_AXIS(1.0,0.0,0.0);
  const Vec3 Y_AXIS(0.0,1.0,0.0);
  const Vec3 Z_AXIS(0.0,0.0,1.0);
}

#endif