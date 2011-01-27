#ifndef DEV_CAMERA_H
#define DEV_CAMERA_H

#include <Kernel/DevInclude.h>
#include <Element/DevElement.h>

namespace dev
{
  class Camera
  {
  public:
    Camera();
    Camera(Vec3 position, Vec3 look, Vec3 up, 
           float fovY, float aspect, float znear, float zfar);
    virtual ~Camera();

    void SetMove(const float& x, const float& y, const float& z);
    void SetMove(const Vec3& value);

    void SetPosition(const float& x, const float& y, const float& z);
    void SetPosition(const Vec3& value);
    inline const Vec3& GetPosition() const
    {
      return _position();
    }

    void SetLook(const float& x, const float& y, const float& z);
    void SetLook(const Vec3& value);
    inline const Vec3& GetLook() const
    {
      return _look();
    }

    void SetUp(const float& x, const float& y, const float& z);
    void SetUp(const Vec3& value);
    inline const Vec3& GetUp() const
    {
      return _up();
    }

    void SetDirection(const float& x, const float& y, const float& z);
    void SetDirection(const Vec3& value);
    inline const Vec3& GetDirection() const
    {
      return _direction;
    }

    inline const Vec3& GetRight() const
    {
      return _right;
    }

    void  SetNewProjection(float fovY, float aspect, float znear, float zfar);
    inline float GetFovYProjection() const
    {
      return _fovY();
    }

    inline float GetAspectProjection() const
    {
      return _aspect();
    }

    inline float GetZNearProjection() const
    {
      return _zn();
    }

    inline float GetZFarProjection() const
    {
      return _zf();
    }

    inline const Matrix& GetViewMatrix() const
    {
      return _view;
    }

    inline const Matrix& GetProjectionMatrix() const
    {
      return _projection;
    }

    void Update();

  protected:
    void updateDirectionAndRight();
    Matrix _view, _projection;
    bool   _updateView;

    Properties::Float   _fovY, _aspect, _zn, _zf;
    Properties::Vector3 _position;
    Properties::Vector3 _look;
    Properties::Vector3 _up;

    Vec3   _direction;
    Vec3   _right;
  };
}

#endif