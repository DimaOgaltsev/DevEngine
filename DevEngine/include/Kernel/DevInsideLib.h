#ifndef DEV_INSIDE_LIB_H
#define DEV_INSIDE_LIB_H

#include <Kernel/DevTimer.h>

namespace dev
{
  class SystemTimer :
    public Timer
  {
  public:
    static Timer* GetTimer()
    {
      static Timer timer;
      return &timer;
    }
  };
}

#endif