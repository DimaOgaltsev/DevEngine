#ifndef DEV_MATH_H
#define DEV_MATH_H

#include <Kernel/DevInclude.h>

namespace dev
{
  namespace Matrix
  {
    inline D3DXMATRIX Identity()
    {
      D3DXMATRIX out;
      D3DXMatrixIdentity(&out);
      return out;
    }
    //translate
    inline D3DXMATRIX Translate(D3DXVECTOR3* translate)
    {
      D3DXMATRIX out;
      D3DXMatrixTranslation(&out, translate->x, translate->y, translate->z);
      return out;
    }

    inline D3DXMATRIX Translate(float x, float y, float z)
    {
      D3DXMATRIX out;
      D3DXMatrixTranslation(&out, x, y, z);
      return out;
    }
    //rotation
    inline D3DXMATRIX Rotation(D3DXVECTOR3* anglesEuler)
    {
      D3DXMATRIX out;
      D3DXMatrixRotationYawPitchRoll(&out, anglesEuler->x, anglesEuler->y, anglesEuler->z); 
      return out;
    }

    inline D3DXMATRIX Rotation(float xAngle, float yAngle, float zAngle)
    {
      D3DXMATRIX out;
      D3DXMatrixRotationYawPitchRoll(&out, xAngle, yAngle, zAngle);
      return out;
    }

    inline D3DXMATRIX Rotation(D3DXQUATERNION* quat)
    {
      D3DXMATRIX out;
      D3DXMatrixRotationQuaternion(&out, quat);
      return out;
    }

    //scale
    inline D3DXMATRIX Scale(D3DXVECTOR3* scale)
    {
      D3DXMATRIX out;
      D3DXMatrixScaling(&out, scale->x, scale->y, scale->z);
      return out;
    }

    inline D3DXMATRIX Scale(float x, float y, float z)
    {
      D3DXMATRIX out;
      D3DXMatrixScaling(&out, x, y, z);
      return out;
    }

    //look
    inline D3DXMATRIX Look(D3DXVECTOR3* position, D3DXVECTOR3* look, D3DXVECTOR3* up)
    {
      D3DXMATRIX out;
      D3DXMatrixLookAtLH(&out, position, look, up);
      return out;
    }

    //projection
    inline D3DXMATRIX Projection(float fovY, float aspect, float znear, float zfar)
    {
      D3DXMATRIX out;
      D3DXMatrixPerspectiveFovLH(&out, fovY, aspect, znear, zfar);
      return out;
    }
  }
}

#endif