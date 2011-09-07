#ifndef DEV_MANIPULATOR_WASD_H
#define DEV_MANIPULATOR_WASD_H

#include <Kernel/DevInclude.h>

#include <Math/DevMath.h>
#include <Manipulator/DevManipulator.h>

namespace dev
{
  class ManipulatorWASD : public Manipulator
  {
  public:
    ManipulatorWASD();
    virtual ~ManipulatorWASD();
    virtual void Update(Camera& camera);

  protected:
    float _mouseX, _mouseY;
  };
}

#endif