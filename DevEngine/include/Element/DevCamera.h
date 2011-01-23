#ifndef DEV_CAMERA_H
#define DEV_CAMERA_H

#include <Kernel/DevInclude.h>
#include <Element/DevElement.h>

namespace dev
{
  class Camera
  {
  public:
    Camera(Vec3 position, Vec3 look, Vec3 up, 
           float fovY, float aspect, float znear, float zfar);
    virtual ~Camera();

    void SetPosition(Vec3 value);
    Vec3 GetPosition();

    void SetLook(Vec3 value);
    Vec3 GetLook();

    void SetUp(Vec3 value);
    Vec3 GetUp();

    void SetDirection(Vec3 value);
    Vec3 GetDirection();

    void  SetNewProjection(float fovY, float aspect, float znear, float zfar);
    float GetFovYProjection();
    float GetAspectProjection();
    float GetZNearProjection();
    float GetZFarProjection();

    Matrix GetViewMatrix();
    Matrix GetProjectionMatrix();

  protected:
    Matrix _view, _projection;
    bool   _updateView;

    Properties::Float   _fovY, _aspect, _zn, _zf;
    Properties::Vector3 _position;
    Properties::Vector3 _look;
    Properties::Vector3 _up;
  };
}

#endif