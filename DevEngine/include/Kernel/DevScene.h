#ifndef DEV_SCENE_H
#define DEV_SCENE_H

#include <Kernel/DevInclude.h>

#include <Element/DevCamera.h>
#include <Element/DevGroup.h>

namespace dev
{
  class Scene :
    public Object
  {
  public:
    Scene();
    Scene(Camera* camera);
    virtual ~Scene();

    void SetActivCamera(Camera* camera);
    Camera* GetActivCamera();

    void AddElement(Element* element);
    void RemoveElement(Element* element);
    inline Element* GetElement(unsigned int num)
    {
      return _mainGroup->GetElement(num);
    }

    void Update();

  protected:
    Camera* _cameraActive;
    Group*  _mainGroup;
  };
}

#endif