#ifndef DEV_MATH_H
#define DEV_MATH_H

#include <Kernel/DevInclude.h>

namespace dev
{
  namespace Matrix
  {
    inline static D3DXMATRIX Identity();

    //translate
    inline static D3DXMATRIX Translate(D3DXVECTOR3* translate);
    inline static D3DXMATRIX Translate(float x, float y, float z);
    
    //rotation
    inline static D3DXMATRIX Rotation(D3DXVECTOR3* anglesEuler);
    inline static D3DXMATRIX Rotation(float xAngle, float yAngle, float zAngle);
    inline static D3DXMATRIX Rotation(D3DXQUATERNION* quat);

    //scale
    inline static D3DXMATRIX Scale(D3DXVECTOR3* scale);
    inline static D3DXMATRIX Scale(float x, float y, float z);

    //look
    inline static D3DXMATRIX Look(D3DXVECTOR3* position, D3DXVECTOR3* look, D3DXVECTOR3* up);

    //projection
    inline static D3DXMATRIX Projection(float fovY, float aspect, float znear, float zfar);
  }

  //inline static
  inline D3DXMATRIX Matrix::Identity()
  {
    D3DXMATRIX out;
    D3DXMatrixIdentity(&out);
    return out;
  }

  inline D3DXMATRIX Matrix::Translate(D3DXVECTOR3* translate)
  {
    D3DXMATRIX out;
    D3DXMatrixTranslation(&out, translate->x, translate->y, translate->z);
    return out;
  }

  inline D3DXMATRIX Matrix::Translate(float x, float y, float z)
  {
    D3DXMATRIX out;
    D3DXMatrixTranslation(&out, x, y, z);
    return out;
  }

  inline D3DXMATRIX Matrix::Rotation(D3DXVECTOR3* anglesEuler)
  {
    D3DXMATRIX out;
    D3DXMatrixRotationYawPitchRoll(&out, anglesEuler->x, anglesEuler->y, anglesEuler->z); 
    return out;
  }

  inline D3DXMATRIX Matrix::Rotation(float xAngle, float yAngle, float zAngle)
  {
    D3DXMATRIX out;
    D3DXMatrixRotationYawPitchRoll(&out, xAngle, yAngle, zAngle);
    return out;
  }

  inline D3DXMATRIX Matrix::Rotation(D3DXQUATERNION* quat)
  {
    D3DXMATRIX out;
    D3DXMatrixRotationQuaternion(&out, quat);
    return out;
  }

  inline D3DXMATRIX Matrix::Scale(D3DXVECTOR3* scale)
  {
    D3DXMATRIX out;
    D3DXMatrixScaling(&out, scale->x, scale->y, scale->z);
    return out;
  }

  inline D3DXMATRIX Matrix::Scale(float x, float y, float z)
  {
    D3DXMATRIX out;
    D3DXMatrixScaling(&out, x, y, z);
    return out;
  }

  inline D3DXMATRIX Matrix::Look(D3DXVECTOR3* position, D3DXVECTOR3* look, D3DXVECTOR3* up)
  {
    D3DXMATRIX out;
    D3DXMatrixLookAtLH(&out, position, look, up);
    return out;
  }

  inline D3DXMATRIX Matrix::Projection(float fovY, float aspect, float znear, float zfar)
  {
    D3DXMATRIX out;
    D3DXMatrixPerspectiveFovLH(&out, fovY, aspect, znear, zfar);
    return out;
  }
}

#endif