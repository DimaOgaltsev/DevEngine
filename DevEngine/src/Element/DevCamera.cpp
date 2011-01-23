#include <Element/DevCamera.h>

#include <Math/DevMatrix.h>

using namespace dev;

Camera::Camera(Vec3 position, Vec3 look, Vec3 up, 
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

void Camera::SetPosition(Vec3 value)
{
  _look = value + GetDirection();
  _position = value;
  _updateView = true;
}

Vec3 Camera::GetPosition()
{
  return _position();
}

void Camera::SetLook(Vec3 value)
{
  _look = value;
  _updateView = true;
}

Vec3 Camera::GetLook()
{
  return _look();
}

void Camera::SetUp(Vec3 value)
{
  value.Normalize();
  _up = value;
  _updateView = true;
}

Vec3 Camera::GetUp()
{
  return _up();
}

void Camera::SetDirection(Vec3 value)
{
  value.Normalize();
  _look = _position() + value;
  _updateView = true;
}

Vec3 Camera::GetDirection()
{
  Vec3 direction = (_look() - _position());
  direction.Normalize();
  return direction;
}

void Camera::SetNewProjection(float fovY, float aspect, float znear, float zfar)
{
  _fovY = fovY;
  _aspect = aspect;
  _zn = znear;
  _zf = zfar;
  _projection = Matrix::Projection(fovY, aspect, znear, zfar);
}

float Camera::GetFovYProjection()
{
  return _fovY();
}

float Camera::GetAspectProjection()
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

Matrix Camera::GetViewMatrix()
{
  if (_updateView)
  {
    _view = Matrix::Look(GetPosition(), GetLook(), GetUp());
    _updateView = false;
  }
  return _view;
}

Matrix Camera::GetProjectionMatrix()
{
  return _projection;
}
