#include <Element/DevCamera.h>

#include <Kernel/DevMath.h>

using namespace dev;

Camera::Camera(D3DXVECTOR3 position, D3DXVECTOR3 look, D3DXVECTOR3 up, 
               float width, float height, float znear, float zfar) :
  _updateView(true)
{
  SetPosition(position);
  SetLook(look);
  SetUp(up);
  SetNewProjection(width, height, znear, zfar);
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

void Camera::SetNewProjection(float width, float height, float znear, float zfar)
{
  _w = width;
  _h = height;
  _zn = znear;
  _zf = zfar;
  _projection = Matrix::Projection(width, height, znear, zfar);
}

float Camera::GetWidthProjection()
{
  return _w();
}

float Camera::GetHeightProjection()
{
  return _h();
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
