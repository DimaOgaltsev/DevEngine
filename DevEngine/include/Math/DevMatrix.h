#ifndef DEV_MATRIX_H
#define DEV_MATRIX_H

#include <Math/DevVec2.h>
#include <Math/DevVec3.h>
#include <Math/DevVec4.h>

namespace dev
{
  class Matrix
  {
  protected:
  #define ROW(row, v1, v2, v3, v4 ) \
              m[(row)][0] = (v1); \
              m[(row)][1] = (v2); \
              m[(row)][2] = (v3); \
              m[(row)][3] = (v4);

  #define RESULT_MM(mat1, mat2, row, column) \
                   (mat1).m[(row)][(column)] = \
                    (m[(row)][0] * (mat2).m[0][(column)]) \
                   +(m[(row)][1] * (mat2).m[1][(column)]) \
                   +(m[(row)][2] * (mat2).m[2][(column)]) \
                   +(m[(row)][3] * (mat2).m[3][(column)])

  #define RESULT_MV4(vec1, vec2, row) \
                    (vec1).v[(row)] = \
                     (m[(row)][0] * (vec).v[0]) \
                    +(m[(row)][1] * (vec).v[1]) \
                    +(m[(row)][2] * (vec).v[2]) \
                    +(m[(row)][3] * (vec).v[3])

  #define RESULT_MV3(vec1, vec2, row) \
                    (vec1).v[(row)] = \
                     (m[(row)][0] * (vec).v[0]) \
                    +(m[(row)][1] * (vec).v[1]) \
                    +(m[(row)][2] * (vec).v[2]) \
                    +(m[(row)][3])

  inline static float
    MINOR(const Matrix& mat, const int r0, const int r1, const int r2, 
                             const int c0, const int c1, const int c2)
  {
    return mat.m[r0][c0] * (mat.m[r1][c1] * mat.m[r2][c2] - mat.m[r2][c1] * mat.m[r1][c2]) -
           mat.m[r0][c1] * (mat.m[r1][c0] * mat.m[r2][c2] - mat.m[r2][c0] * mat.m[r1][c2]) +
           mat.m[r0][c2] * (mat.m[r1][c0] * mat.m[r2][c1] - mat.m[r2][c0] * mat.m[r1][c1]);
  }

  public:
    union 
    {
      struct 
      {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
      };
      float m[4][4];
    };

    Matrix()
    {
      Identity();
    }

    Matrix(const Matrix& matrix)
    {
      memcpy(&m, &matrix, 16 * sizeof(float));
    }

    Matrix(float m00, float m01, float m02, float m03,
           float m10, float m11, float m12, float m13,
           float m20, float m21, float m22, float m23,
           float m30, float m31, float m32, float m33)
    {
      ROW(0, m00, m01, m02, m03);
      ROW(1, m10, m11, m12, m13);
      ROW(2, m20, m21, m22, m23);
      ROW(3, m30, m31, m32, m33);
    }

    //operators
    inline void Identity()
    {
      ROW(0,  1, 0, 0, 0);
      ROW(1,  0, 1, 0, 0);
      ROW(2,  0, 0, 1, 0);
      ROW(3,  0, 0, 0, 1);
    }

    inline float Determinant() const
    {
      return m[0][0] * MINOR(*this, 1, 2, 3, 1, 2, 3) -
             m[0][1] * MINOR(*this, 1, 2, 3, 0, 2, 3) +
             m[0][2] * MINOR(*this, 1, 2, 3, 0, 1, 3) -
             m[0][3] * MINOR(*this, 1, 2, 3, 0, 1, 2);
    }

    inline void MakeTranspose()
    {
      ROW(0, m00, m10, m20, m30);
      ROW(1, m01, m11, m21, m31);
      ROW(2, m02, m12, m22, m32);
      ROW(3, m03, m13, m23, m33);
    }

    inline static Matrix Transpose(Matrix matrix)
    {
      matrix.MakeTranspose();
      return matrix;
    }

    Matrix Matrix::MakeInverse()
    {
      float v0 = m20 * m31 - m21 * m30;
      float v1 = m20 * m32 - m22 * m30;
      float v2 = m20 * m33 - m23 * m30;
      float v3 = m21 * m32 - m22 * m31;
      float v4 = m21 * m33 - m23 * m31;
      float v5 = m22 * m33 - m23 * m32;

      float t00 = +(v5 * m11 - v4 * m12 + v3 * m13);
      float t10 = -(v5 * m10 - v2 * m12 + v1 * m13);
      float t20 = +(v4 * m10 - v2 * m11 + v0 * m13);
      float t30 = -(v3 * m10 - v1 * m11 + v0 * m12);

      float invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

      float d00 = t00 * invDet;
      float d10 = t10 * invDet;
      float d20 = t20 * invDet;
      float d30 = t30 * invDet;

      float d01 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
      float d11 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
      float d21 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
      float d31 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

      v0 = m10 * m31 - m11 * m30;
      v1 = m10 * m32 - m12 * m30;
      v2 = m10 * m33 - m13 * m30;
      v3 = m11 * m32 - m12 * m31;
      v4 = m11 * m33 - m13 * m31;
      v5 = m12 * m33 - m13 * m32;

      float d02 = +(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
      float d12 = -(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
      float d22 = +(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
      float d32 = -(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

      v0 = m21 * m10 - m20 * m11;
      v1 = m22 * m10 - m20 * m12;
      v2 = m23 * m10 - m20 * m13;
      v3 = m22 * m11 - m21 * m12;
      v4 = m23 * m11 - m21 * m13;
      v5 = m23 * m12 - m22 * m13;

      float d03 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
      float d13 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
      float d23 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
      float d33 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

      ROW(0, d00, d01, d02, d03);
      ROW(1, d10, d11, d12, d13);
      ROW(2, d20, d21, d22, d23);
      ROW(3, d30, d31, d32, d33);
    }

    inline static Matrix Inverse(Matrix matrix)
    {
      matrix.MakeInverse();
      return matrix;
    }

    //translate
    inline void MakeTranslate(const Vec3& translate)
    {
      MakeTranslate(translate.x, translate.y, translate.z);
    }

    inline void MakeTranslate(float x, float y, float z)
    {
      ROW(0,  1, 0, 0, 0);
      ROW(1,  0, 1, 0, 0);
      ROW(2,  0, 0, 1, 0);
      ROW(3,  x, y, z, 1);
    }
    
    inline static Matrix Translate(const Vec3& translate)
    {
      Matrix out;
      out.MakeTranslate(translate);
      return out;
    }

    inline static Matrix Translate(float x, float y, float z)
    {
      Matrix out;
      out.MakeTranslate(x, y, z);
      return out;
    }
    
    //rotation
    inline void MakeRotate(const Vec3& anglesEuler)
    {
      MakeRotate(anglesEuler.x, anglesEuler.y, anglesEuler.z);
    }

    inline void MakeRotate(float xAngle, float yAngle, float zAngle)
    {
      float cosa = cosf(xAngle); float sina = sinf(xAngle);
      float cosb = cosf(yAngle); float sinb = sinf(yAngle);
      float cosc = cosf(zAngle); float sinc = sinf(zAngle);

      ROW(0,                       cosb * cosc,                       cosb * sinc,  cosa * sinb * cosc + sina * sinc,   0);
      ROW(1,  sina * sinb * cosc - cosa * sinc,  sina * sinb * sinc + cosa * cosc,  cosa * sinb * sinc - sina * cosc,   0);
      ROW(2,                             -sinb,                       sina * cosb,                       cosa * cosb,   0);
      ROW(3,                                 0,                                 0,                                 0,   1);
    }

    inline static Matrix Rotate(const Vec3& anglesEuler)
    {
      Matrix out;
      out.MakeRotate(anglesEuler);
      return out;
    }

    inline static Matrix Rotate(float xAngle, float yAngle, float zAngle)
    {
      Matrix out;
      out.MakeRotate(xAngle, yAngle, zAngle);
      return out;
    }

    //scale
    inline void MakeScale(const Vec3& scale)
    {
      MakeScale(scale.x, scale.y, scale.z);
    }

    inline void MakeScale(float x, float y, float z)
    {
      ROW(0,  x, 0, 0, 0);
      ROW(1,  0, y, 0, 0);
      ROW(2,  0, 0, z, 0);
      ROW(3,  0, 0, 0, 1);
    }

    inline static Matrix Scale(const Vec3& scale)
    {
      Matrix out;
      out.MakeScale(scale);
      return out;
    }

    inline static Matrix Scale(float x, float y, float z)
    {
      Matrix out;
      out.MakeScale(x, y, z);
      return out;
    }

    //Transform
    inline void MakeTransform(const Vec3& translate, const Vec3& anglesEuler, const Vec3& scale)
    {
      float cosa = cosf(anglesEuler.x); float sina = sinf(anglesEuler.x);
      float cosb = cosf(anglesEuler.y); float sinb = sinf(anglesEuler.y);
      float cosc = cosf(anglesEuler.z); float sinc = sinf(anglesEuler.z);

      ROW(0,                       scale.x * (cosb * cosc),                       scale.y * (cosb * sinc),  scale.z * (cosa * sinb * cosc + sina * sinc),   0);
      ROW(1,  scale.x * (sina * sinb * cosc - cosa * sinc),  scale.y * (sina * sinb * sinc + cosa * cosc),  scale.z * (cosa * sinb * sinc - sina * cosc),   0);
      ROW(2,                             scale.x * (-sinb),                       scale.y * (sina * cosb),                       scale.z * (cosa * cosb),   0);
      ROW(3,                                   translate.x,                                   translate.y,                                   translate.z,   1);
    }

    inline static Matrix Transform(const Vec3& translate, const Vec3& anglesEuler, const Vec3& scale)
    {
      Matrix out;
      out.MakeTransform(translate, anglesEuler, scale);
      return out;
    }

    //look
    inline void MakeLook(const Vec3& position, const Vec3& look, const Vec3& up)
    {
      Vec3 zAxis = look - position;
      zAxis.Normalize();
      Vec3 xAxis = up ^ zAxis;
      xAxis.Normalize();
      Vec3 yAxis = zAxis ^ xAxis;
      yAxis.Normalize();

      ROW(0,              xAxis.x,             yAxis.x,             zAxis.x, 0);
      ROW(1,              xAxis.y,             yAxis.y,             zAxis.y, 0);
      ROW(2,              xAxis.z,             yAxis.z,             zAxis.z, 0);
      ROW(3,  -(xAxis * position), -(yAxis * position), -(zAxis * position), 1);
    }

    inline static Matrix Look(const Vec3& position, const Vec3& look, const Vec3& up)
    {
      Matrix out;
      out.MakeLook(position, look, up);
      return out;
    }

    //projection
    inline void MakeProjection(float fovY, float aspect, float znear, float zfar)
    {
      float yScale = cosf(fovY * 0.5f) / sinf(fovY * 0.5f);
      float xScale = yScale / aspect;
      float zf = 1 / (zfar - znear);

      ROW(0, xScale,      0,                  0, 0);
      ROW(1,      0, yScale,                  0, 0);
      ROW(2,      0,      0,          zfar * zf, 1);
      ROW(3,      0,      0, -znear * zfar * zf, 0);
    }

    inline static Matrix Projection(float fovY, float aspect, float znear, float zfar)
    {
      Matrix out;
      out.MakeProjection(fovY, aspect, znear, zfar);
      return out;
    }

    //operators
    inline bool operator == (const Matrix& matrix) const 
    { 
      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
        if (m[i][j] != matrix.m[i][j])
          return false;
      }
      return true;
    }

    inline bool operator != (const Matrix& matrix) const 
    {
      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
        if (m[i][j] == matrix.m[i][j])
          return false;
      }
      return true;
    }

    inline bool operator < (const Matrix& matrix) const 
    { 
      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
        if (m[i][j] >= matrix.m[i][j])
          return false;
      }
      return true;
    }

    inline bool operator <= (const Matrix& matrix) const 
    { 
      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
        if (m[i][j] > matrix.m[i][j])
          return false;
      }
      return true;
    }

    inline bool operator > (const Matrix& matrix) const 
    { 
      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
        if (m[i][j] <= matrix.m[i][j])
          return false;
      }
      return true;
    }

    inline bool operator >= (const Matrix& matrix) const 
    { 
      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
        if (m[i][j] < matrix.m[i][j])
          return false;
      }
      return true;
    }

    inline Matrix& operator *= (const float& scalar)
    {
      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
        m[i][j] *= scalar;
      }

      return *this;
    }

    inline const Matrix operator * (const float& scalar) const
    {
      Matrix r;

      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
       r.m[i][j] = m[i][j] * scalar;
      }

      return r;
    }

    inline const Vec4 operator * (const Vec4& vec) const
    {
      Vec4 r;

      RESULT_MV4(r, vec, 0);
      RESULT_MV4(r, vec, 1);
      RESULT_MV4(r, vec, 2);
      RESULT_MV4(r, vec, 3);

      return r;
    }

    inline const Vec3 operator * (const Vec3& vec) const
    {
      Vec3 r;

      RESULT_MV3(r, vec, 0);
      RESULT_MV3(r, vec, 1);
      RESULT_MV3(r, vec, 2);
      
      r.v[0] += m30;
      r.v[1] += m31;
      r.v[2] += m32;

      return r;
    }

    inline const Matrix operator * (const Matrix& matrix) const
    {
      Matrix r;

      RESULT_MM(r, matrix, 0, 0);
      RESULT_MM(r, matrix, 0, 1);
      RESULT_MM(r, matrix, 0, 2);
      RESULT_MM(r, matrix, 0, 3);

      RESULT_MM(r, matrix, 1, 0);
      RESULT_MM(r, matrix, 1, 1);
      RESULT_MM(r, matrix, 1, 2);
      RESULT_MM(r, matrix, 1, 3);

      RESULT_MM(r, matrix, 2, 0);
      RESULT_MM(r, matrix, 2, 1);
      RESULT_MM(r, matrix, 2, 2);
      RESULT_MM(r, matrix, 2, 3);

      RESULT_MM(r, matrix, 3, 0);
      RESULT_MM(r, matrix, 3, 1);
      RESULT_MM(r, matrix, 3, 2);
      RESULT_MM(r, matrix, 3, 3);

      return r;
    }

    inline Matrix& operator *= (const Matrix& matrix)
    {
      RESULT_MM(*this, matrix, 0, 0);
      RESULT_MM(*this, matrix, 0, 1);
      RESULT_MM(*this, matrix, 0, 2);
      RESULT_MM(*this, matrix, 0, 3);

      RESULT_MM(*this, matrix, 1, 0);
      RESULT_MM(*this, matrix, 1, 1);
      RESULT_MM(*this, matrix, 1, 2);
      RESULT_MM(*this, matrix, 1, 3);

      RESULT_MM(*this, matrix, 2, 0);
      RESULT_MM(*this, matrix, 2, 1);
      RESULT_MM(*this, matrix, 2, 2);
      RESULT_MM(*this, matrix, 2, 3);

      RESULT_MM(*this, matrix, 3, 0);
      RESULT_MM(*this, matrix, 3, 1);
      RESULT_MM(*this, matrix, 3, 2);
      RESULT_MM(*this, matrix, 3, 3);
      return *this;
    }

    inline const Matrix operator / (const float& scalar) const
    {
      Matrix r;

      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
       r.m[i][j] = m[i][j] / scalar;
      }

      return r;
    }

    inline Matrix& operator /= (const float& scalar)
    {
      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
        m[i][j] /= scalar;
      }

      return *this;
    }

    inline const Matrix operator + (const Matrix& matrix) const
    {
      Matrix r;

      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
       r.m[i][j] = m[i][j] + matrix.m[i][j];
      }

      return r;
    }

    inline Matrix& operator += (const Matrix& matrix)
    {
      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
        m[i][j] += matrix.m[i][j];
      }

      return *this;
    }

    inline const Matrix operator + (const float& scalar) const
    {
      Matrix r;

      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
       r.m[i][j] = m[i][j] + scalar;
      }

      return r;
    }

    inline Matrix& operator += (const float& scalar)
    {
      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
        m[i][j] += scalar;
      }
      return *this;
    }

    inline const Matrix operator - (const Matrix& matrix) const
    {
      Matrix r;

      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
       r.m[i][j] = m[i][j] - matrix.m[i][j];
      }

      return r;
    }

    inline Matrix& operator -= (const Matrix& matrix)
    {
      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
        m[i][j] -= matrix.m[i][j];
      }

      return *this;
    }

    inline const Matrix operator - (const float& scalar) const
    {
      Matrix r;

      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
       r.m[i][j] = m[i][j] - scalar;
      }

      return r;
    }

    inline Matrix& operator -= (const float& scalar)
    {
      for (int i = 0, j = 0; i < 4 && j < 4; i++, j++)
      {
        m[i][j] -= scalar;
      }

      return *this;
    }
  };
}

#endif