#include <Kernel/DevMath.h>

using namespace dev;

D3DXMATRIX Matrix::Identity()
{
  D3DXMATRIX out;
  D3DXMatrixIdentity(&out);
  return out;
}

//translation
D3DXMATRIX Matrix::Translate(D3DXVECTOR3 translate)
{
  D3DXMATRIX out;
  D3DXMatrixTranslation(&out, translate.x, translate.y, translate.z);
  return out;
}

D3DXMATRIX Matrix::Translate(float x, float y, float z)
{
  D3DXMATRIX out;
  D3DXMatrixTranslation(&out, x, y, z);
  return out;
}

//rotation
D3DXMATRIX Matrix::Rotation(D3DXVECTOR3 anglesEuler)
{
  D3DXMATRIX out;
  D3DXMatrixRotationYawPitchRoll(&out, anglesEuler.x, anglesEuler.y, anglesEuler.z); 
  return out;
}

D3DXMATRIX Matrix::Rotation(float xAngle, float yAngle, float zAngle)
{
  D3DXMATRIX out;
  D3DXMatrixRotationYawPitchRoll(&out, xAngle, yAngle, zAngle);
  return out;
}

D3DXMATRIX Matrix::Rotation(D3DXQUATERNION quat)
{
  D3DXMATRIX out;
  D3DXMatrixRotationQuaternion(&out, &quat);
  return out;
}

//scale
D3DXMATRIX Matrix::Scale(D3DXVECTOR3 scale)
{
  D3DXMATRIX out;
  D3DXMatrixScaling(&out, scale.x, scale.y, scale.z);
  return out;
}

D3DXMATRIX Matrix::Scale(float x, float y, float z)
{
  D3DXMATRIX out;
  D3DXMatrixScaling(&out, x, y, z);
  return out;
}
