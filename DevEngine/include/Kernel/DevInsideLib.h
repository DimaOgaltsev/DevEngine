#ifndef DEV_INSIDE_LIB_H
#define DEV_INSIDE_LIB_H

#include <Kernel/DevSingleton.h>
#include <Kernel/DevTimer.h>
#include <Kernel/DevSync.h>
#include <Kernel/DevInput.h>

namespace dev
{
  class SystemCS : public Singleton<CriticalSection>
  {};

  class SystemTimer : public Singleton<Timer>
  {};

  class SystemInput : public Singleton<Input>
  {};
}

#endif