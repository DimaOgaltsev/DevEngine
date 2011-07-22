#ifndef DEV_INSIDE_LIB_H
#define DEV_INSIDE_LIB_H

#include <Kernel/DevTimer.h>
#include <Kernel/DevSync.h>

namespace dev
{
  template<class T>
  class Singleton
  {
  public:
    static T* Get()
    {
      static T* element = new T();
      return element;
    }
  };

  class SystemCS : public Singleton<CriticalSection>
  {};

  class SystemTimer : public Singleton<Timer>
  {};
}

#endif