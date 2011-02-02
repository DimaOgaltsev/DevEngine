#ifndef DEV_QUAT_H
#define DEV_QUAT_H

#include <Math/DevVec4.h>
#include <Math/DevVec3.h>

namespace dev
{
  class Quat
  {
  public:
    union
    {
      struct
      {
        float x, y, z, w;
      };
      float q[4];
    };

    Quat() 
    {
      q[0] = 0.0f;
      q[1] = 0.0f;
      q[2] = 0.0f;
      q[3] = 1.0f;
    }

    Quat(const Vec4& vec)
    {
      q[0] = vec.v[0];
      q[1] = vec.v[1];
      q[2] = vec.v[2];
      q[3] = vec.v[3];
    }

    Quat(const float& x, const float& y, const float& z, const float& Angle)
    {
      MakeRotate(x, y, z, Angle);
    }

    Quat(const Vec3& vec, const float& Angle)
    {
      MakeRotate(vec, Angle);
    }

    inline Vec4 AsVec4()
    {
      return Vec4(x, y, z, w);
    }

    inline Vec3 AsVec3()
    {
      return Vec3(x, y, z);
    }

    inline void MakeRotate(const float& x, const float& y, const float& z, const float& Angle)
    {
      MakeRotate(Vec3(x, y, z), Angle);
    }

    inline void MakeRotate(const Vec3& vec, const float& Angle)
    {
      float length = vec.Length();
      if (length < FLT_EPSILON)
      {
        *this = Quat();
        return;
      }

      float coshalfangle = cosf(0.5f * Angle);
      float sinhalfangle = sinf(0.5f * Angle) / length;

      q[0] = vec.x * sinhalfangle;
      q[1] = vec.y * sinhalfangle;
      q[2] = vec.z * sinhalfangle;
      q[3] = coshalfangle;
    }

    inline void GetRotate(float& x, float& y, float& z, float Angle) const
    {
      float sinhalfangle = sqrt(pow(q[0], 2) + pow(q[1], 2) + pow(q[2], 2));

      Angle = 2.0f * atan2f(sinhalfangle, w);
      if(sinhalfangle)
      {
        x = q[0] / sinhalfangle;
        y = q[1] / sinhalfangle;
        z = q[2] / sinhalfangle;
      }
      else
      {
        x = 0.0;
        y = 0.0;
        z = 1.0;
      }
    }

    inline void GetRotate(Vec3& vec, float& Angle) const
    {
      float sinhalfangle = sqrt(pow(q[0], 2) + pow(q[1], 2) + pow(q[2], 2));

      Angle = 2.0f * atan2f(sinhalfangle, w);
      if(sinhalfangle)
      {
        vec.x = q[0] / sinhalfangle;
        vec.y = q[1] / sinhalfangle;
        vec.z = q[2] / sinhalfangle;
      }
      else
      {
        vec.x = 0.0;
        vec.y = 0.0;
        vec.z = 1.0;
      }
    }

    inline bool operator == (const Quat& quat) const 
    { 
      return (x == quat.x && y == quat.y && z == quat.z && w == quat.w); 
    }

    inline bool operator != (const Quat& quat) const 
    {
      return (x != quat.x || y != quat.y || z != quat.z || w != quat.w); 
    }

    inline bool operator < (const Quat& quat) const 
    { 
      return (x < quat.x && y < quat.y && z < quat.z && w < quat.w);
    }

    inline bool operator <= (const Quat& quat) const 
    { 
      return (x <= quat.x && y <= quat.y && z <= quat.z && w <= quat.w); 
    }

    inline bool operator > (const Quat& quat) const 
    { 
      return (x > quat.x && y > quat.y && z > quat.z && w > quat.w);
    }

    inline bool operator >= (const Quat& quat) const 
    { 
      return (x >= quat.x && y >= quat.y && z >= quat.z && w >= quat.w); 
    }

    inline Quat& operator *= (const float& scalar)
    {
      x *= scalar;
      y *= scalar;
      z *= scalar;
      w *= scalar;
      return *this;
    }

    inline const Quat operator * (const float& scalar) const
    {
      return Quat(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    inline const Quat operator * (const Quat& quat) const
    {
      return Quat( quat.w * x + quat.x * w + quat.y * z - quat.z * y,
                   quat.w * y - quat.x * z + quat.y * w + quat.z * x,
                   quat.w * z + quat.x * y - quat.y * x + quat.z * w,
                   quat.w * w - quat.x * x - quat.y * y - quat.z * z );
    }

    inline Quat& operator *= (const Quat& quat)
    {
      float bx = quat.w * x + quat.x * w + quat.y * z - quat.z * y;
      float by = quat.w * y - quat.x * z + quat.y * w + quat.z * x;
      float bz = quat.w * z + quat.x * y - quat.y * x + quat.z * w;
      w = quat.w * w - quat.x * x - quat.y * y - quat.z * z;

      x = bx;
      y = by;
      z = bz;

      return (*this);
    }

    inline Quat operator / (const float& scalar) const
    {
      float div = 1.0f / scalar;
      return Quat(x * div, y * div, z * div, w * div);
    }

    inline Quat& operator /= (const float& scalar)
    {
      float div = 1.0f / scalar;
      x *= div;
      y *= div;
      z *= div;
      w *= div;
      return *this;
    }
    
    inline const Quat operator / (const Quat& quat) const
    {
        return ((*this) * quat.inverse());
    }

    inline Quat& operator /= (const Quat& quat)
    {
        (*this) = (*this) * quat.inverse();
        return (*this);
    }

    inline const Quat operator + (const Quat& quat) const
    {
        return Quat(x + quat.x, y + quat.y,
                    z + quat.z, w + quat.w);
    }

    inline Quat& operator += (const Quat& quat)
    {
        x += quat.x;
        y += quat.y;
        z += quat.z;
        w += quat.w;
        return *this;
    }

    inline const Quat operator - (const Quat& quat) const
    {
        return Quat(x - quat.x, y - quat.y,
                    z - quat.z, w - quat.w );
    }

    inline Quat& operator -= (const Quat& quat)
    {
        x -= quat.x;
        y -= quat.y;
        z -= quat.z;
        w -= quat.w;
        return *this;
    }

    inline const Quat operator - () const
    {
        return Quat (-x, -y, -z, -w);
    }

    float Length() const
    {
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
    }

    float Length2() const
    {
        return pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2);
    }

    inline Quat Conj() const
    { 
         return Quat(-x, -y, -z, w);
    }

    inline const Quat inverse () const
    {
         return Conj() / Length2();
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