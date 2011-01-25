#ifndef DEV_VEC4_H
#define DEV_VEC4_H

#include <Math/DevVec3.h>

namespace dev
{
  class Vec4
  {
  public:
    union
    {
      struct
      {
        float x, y, z, w;
      };
      float v[4];
    };

    Vec4() 
    { 
      v[0] = 0;
      v[1] = 0;
      v[2] = 0;
      v[3] = 0;
    }

    Vec4(float x, float y, float z, float w)
    {
      v[0] = x;
      v[1] = y;
      v[2] = z;
      v[3] = w;
    };

    Vec4(const Vec3& vec, float w)
    {
      v[0] = vec.x;
      v[1] = vec.y;
      v[2] = vec.z;
      v[3] = w;
    }

    Vec4(const Vec4& vec)
    {
      v[0] = vec.x;
      v[1] = vec.y;
      v[2] = vec.z;
      v[3] = vec.w;
    }

    inline Vec3 AsVec3()
    {
      return Vec3(x, y, z);
    }

    //operators
    inline bool operator == (const Vec4& vec) const 
    { 
      return (x == vec.x && y == vec.y && z == vec.z && w == vec.w); 
    }

    inline bool operator != (const Vec4& vec) const 
    {
      return (x != vec.x || y != vec.y || z != vec.z || w != vec.w); 
    }

    inline bool operator < (const Vec4& vec) const 
    { 
      return (x < vec.x && y < vec.y && z < vec.z && w < vec.w);
    }

    inline bool operator <= (const Vec4& vec) const 
    { 
      return (x <= vec.x && y <= vec.y && z <= vec.z && w <= vec.w); 
    }

    inline bool operator > (const Vec4& vec) const 
    { 
      return (x > vec.x && y > vec.y && z > vec.z && w > vec.w);
    }

    inline bool operator >= (const Vec4& vec) const 
    { 
      return (x >= vec.x && y >= vec.y && z >= vec.z && w >= vec.w); 
    }

    inline Vec4& operator *= (const float& scalar)
    {
      x *= scalar;
      y *= scalar;
      z *= scalar;
      w *= scalar;
      return *this;
    }

    inline const Vec4 operator * (const float& scalar) const
    {
      return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    inline float operator * (const Vec4& vec) const
    {
      return (x * vec.x + y * vec.y + z * vec.z + w * vec.w);
    }

    inline const Vec4 operator / (const float& scalar) const
    {
      return Vec4(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    inline Vec4& operator /= (const float& scalar)
    {
      x /= scalar;
      y /= scalar;
      z /= scalar;
      w /= scalar;
      return *this;
    }

    inline const Vec4 operator + (const Vec4& vec) const
    {
      return Vec4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
    }

    inline Vec4& operator += (const Vec4& vec)
    {
      x += vec.x;
      y += vec.y;
      z += vec.z;
      w += vec.w;
      return *this;
    }

    inline const Vec4 operator + (const float& scalar) const
    {
      return Vec4(x + scalar, y + scalar, z + scalar, w + scalar);
    }

    inline Vec4& operator += (const float& scalar)
    {
      x += scalar;
      y += scalar;
      z += scalar;
      w += scalar;
      return *this;
    }

    inline const Vec4 operator - (const Vec4& vec) const
    {
      return Vec4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
    }

    inline Vec4& operator -= (const Vec4& vec)
    {
      x -= vec.x;
      y -= vec.y;
      z -= vec.z;
      w -= vec.w;
      return *this;
    }

    inline const Vec4 operator - (const float& scalar) const
    {
      return Vec4(x - scalar, y - scalar, z - scalar, w - scalar);
    }

    inline Vec4& operator -= (const float& scalar)
    {
      x -= scalar;
      y -= scalar;
      z -= scalar;
      w -= scalar;
      return *this;
    }

    inline const Vec4 operator - () const
    {
      return Vec4(-x, -y, -z, -w);
    }

    inline float Length() const
    {
      return sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
    }

    inline float Length2(void) const
    {
      return pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2);
    }

    inline void operator = (const Vec4& vec)
    {
      x = vec.x;
      y = vec.y;
      z = vec.z;
      w = vec.w;
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
        w *= inv;
      }
      return norm;
    }
  };
}

#endif