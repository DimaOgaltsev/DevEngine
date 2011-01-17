#include <Element/DevCamera.h>

#include <Kernel/DevMath.h>

using namespace dev;

Camera::Camera(D3DXVECTOR3 position, D3DXVECTOR3 look, D3DXVECTOR3 up, 
               float fovY, float aspect, float znear, float zfar) :
  _updateView(true)
{
  SetPosition(position);
  SetLook(look);
  SetUp(up);
  SetNewProjection(fovY, aspect, znear, zfar);
}

Camera::~Camera()
{
}

void Camera::SetPosition(D3DXVECTOR3 value)
{
  _position = value;
  _updateView = true;
}

D3DXVECTOR3 Camera::GetPosition()
{
  return _position();
}

void Camera::SetLook(D3DXVECTOR3 value)
{
  _look = value;
  _updateView = true;
}

D3DXVECTOR3 Camera::GetLook()
{
  return _look();
}

void Camera::SetUp(D3DXVECTOR3 value)
{
  _up = value;
  _updateView = true;
}

D3DXVECTOR3 Camera::GetUp()
{
  return _up();
}

void Camera::SetNewProjection(float fovY, float aspect, float znear, float zfar)
{
  _fovY = fovY;
  _aspect = aspect;
  _zn = znear;
  _zf = zfar;
  _projection = Matrix::Projection(fovY,aspect, znear, zfar);
}

float Camera::GetWidthProjection()
{
  return _fovY();
}

float Camera::GetHeightProjection()
{
  return _aspect();
}

float Camera::GetZNearProjection()
{
  return _zn();
}

float Camera::GetZFarProjection()
{
  return _zf();
}

D3DXMATRIX Camera::GetViewMatrix()
{
  if (_updateView)
  {
    _view = Matrix::Look(&GetPosition(), &GetLook(), &GetUp());
    _updateView = false;
  }
  return _view;
}

D3DXMATRIX Camera::GetProjectionMatrix()
{
  return _projection;
}
