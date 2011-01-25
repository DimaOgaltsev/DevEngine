#include <Element/DevCamera.h>

#include <Math/DevMatrix.h>

using namespace dev;

dev::Camera::Camera() :
  _updateView(true)
{
  SetPosition(Vec3(0, 0, -10));
  SetLook(Vec3(0, 0, 0));
  SetUp(Vec3(0, 1, 0));
  SetNewProjection(dev::PI_4, 1.333f, 1.0f, 250.0f);
}

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

void Camera::SetPosition(const Vec3& value)
{
  _look = value + GetDirection();
  _position = value;
  updateDirectionAndRight();
  _updateView = true;
}

void Camera::SetLook(const Vec3& value)
{
  _look = value;
  updateDirectionAndRight();
  _updateView = true;
}

void Camera::SetUp(const Vec3& value)
{
  Vec3 buf(value);
  buf.Normalize();
  _up = buf;
  updateDirectionAndRight();
  _updateView = true;
}

void Camera::SetDirection(const Vec3& value)
{
  _look = _position() + value;
  updateDirectionAndRight();
  _updateView = true;
}

void Camera::SetNewProjection(float fovY, float aspect, float znear, float zfar)
{
  _fovY = fovY;
  _aspect = aspect;
  _zn = znear;
  _zf = zfar;
  _projection = Matrix::Projection(fovY, aspect, znear, zfar);
}

void Camera::Update()
{
  if (_updateView)
  {
    _view = Matrix::Look(GetPosition(), GetLook(), GetUp());
    _updateView = false;
  }
}


void dev::Camera::updateDirectionAndRight()
{
  _direction = (_look() - _position());
  _direction.Normalize();
  _right = _up() ^ _direction;
  _right.Normalize();
}
