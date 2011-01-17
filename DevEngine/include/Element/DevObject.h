#ifndef DEV_OBJECT_H
#define DEV_OBJECT_H

#include <Kernel/DevInclude.h>

namespace dev
{
  class Object
  {
  protected:
    static LPDIRECT3D9        _directX;
    static LPDIRECT3DDEVICE9  _deviceDX;
  };
}

#endif