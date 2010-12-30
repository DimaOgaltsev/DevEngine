#ifndef DEV_CAMERA_H
#define DEV_CAMERA_H

#include <Kernel/DevInclude.h>
#include <Element/DevElement.h>

namespace dev
{
  class Camera
  {
  public:
    Camera(D3DXVECTOR3 position, D3DXVECTOR3 look, D3DXVECTOR3 up, float width, float height, float znear, float zfar);
    virtual ~Camera();

    void SetPosition(D3DXVECTOR3 value);
    D3DXVECTOR3 GetPosition();

    void SetLook(D3DXVECTOR3 value);
    D3DXVECTOR3 GetLook();

    void SetUp(D3DXVECTOR3 value);
    D3DXVECTOR3 GetUp();

    void  SetNewProjection(float width, float height, float znear, float zfar);
    float GetWidthProjection();
    float GetHeightProjection();
    float GetZNearProjection();
    float GetZFarProjection();

    D3DXMATRIX GetViewMatrix();
    D3DXMATRIX GetProjectionMatrix();

  protected:
    D3DXMATRIX  _view, _projection;
    bool        _updateView;

    Properties::Float   _w, _h, _zn, _zf;
    Properties::Vector3 _position;
    Properties::Vector3 _look;
    Properties::Vector3 _up;
  };
}

#endif