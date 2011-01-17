#ifndef DEV_SCENE_H
#define DEV_SCENE_H

#include <Kernel/DevInclude.h>

#include <Element/DevCamera.h>
#include <Element/DevGroup.h>

namespace dev
{
  class Scene
  {
  public:
    Scene();
    Scene(Camera* camera);
    virtual ~Scene();

    void SetActivCamera(Camera* camera);
    Camera* GetActivCamera();

    LPDIRECT3DDEVICE9 GetDevice();
    void SetDevice(LPDIRECT3DDEVICE9 device);

    void Update();

  protected:
    Camera* _cameraActive;
    Group*  _mainGroup; 

    LPDIRECT3DDEVICE9 _device;
  };
}

#endif