#ifndef DEV_INSIDE_LIB_H
#define DEV_INSIDE_LIB_H

#include <Kernel/DevTimer.h>
#include <Kernel/DevSync.h>

namespace dev
{
  class SystemCS
  {
  public:
    static CriticalSection* Get()
    {
      static CriticalSection cs;
      return &cs;
    }
  };

  class SystemTimer
  {
  public:
    static Timer* GetTimer()
    {
      static Timer timer;
      return &timer;
    }
  };

  class SystemEvent
  {
  public:
    static Event* GetEvent()
    {
      static Event event("systemEvent");
      return &event;
    }
  };
}

#endif