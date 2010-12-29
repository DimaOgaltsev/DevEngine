#ifndef DEV_MATH_H
#define DEV_MATH_H

#include <Kernel/DevInclude.h>

namespace dev
{
  namespace Matrix
  {
    inline D3DXMATRIX Identity();
    //translate
    inline D3DXMATRIX Translate(D3DXVECTOR3 translate);
    inline D3DXMATRIX Translate(float x, float y, float z);
    //rotation
    inline D3DXMATRIX Rotation(D3DXVECTOR3 anglesEuler);
    inline D3DXMATRIX Rotation(float xAngle, float yAngle, float zAngle);
    inline D3DXMATRIX Rotation(D3DXQUATERNION quat);
    //scale
    inline D3DXMATRIX Scale(D3DXVECTOR3 scale);
    inline D3DXMATRIX Scale(float x, float y, float z);
  }
}

#endif