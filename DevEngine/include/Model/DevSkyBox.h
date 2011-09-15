#ifndef DEV_SKY_BOX_H
#define DEV_SKY_BOX_H

#include <Kernel/DevInclude.h>

#include <Model/DevMesh.h>
#include <Element/DevCamera.h>

namespace dev
{
  class SkyBox : public Mesh
  {
  public:
    SkyBox(const char* name = defaultSBName);
    virtual ~SkyBox();

    void SetCamera(Camera* camera);

    virtual void Update();
    virtual void UpdateParameters();
    virtual void ReturnParameters();

  protected:
    Camera* _camera;
  };
}

#endif