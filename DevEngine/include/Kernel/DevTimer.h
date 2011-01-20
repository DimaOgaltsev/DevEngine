#ifndef DEV_TIMER_H
#define DEV_TIMER_H

#include <Kernel/DevInclude.h>

namespace dev
{
  class Timer
  {
  public:
    Timer();
    virtual ~Timer();

    void Reset(byte numTimer);

    static Timer* GetTimer();

    double GetTimeNS(byte numTimer);
    double GetTimeMkS(byte numTimer);
    double GetTimeMS(byte numTimer);
    double GetTimeS(byte numTimer);
    
    double GetDeltaTimeNS(byte numTimer);
    double GetDeltaTimeMkS(byte numTimer);
    double GetDeltaTimeMS(byte numTimer);
    double GetDeltaTimeS(byte numTimer);

    bool GetEventTimeNS(byte numTimer, double factor);
    bool GetEventTimeMkS(byte numTimer, double factor);
    bool GetEventTimeMS(byte numTimer, double factor);
    bool GetEventTimeS(byte numTimer, double factor);

  protected:

    void   init();

    double getTime(byte numTimer, double factor);

    HANDLE        _thread;
    
    DWORD_PTR     _numProc;
    LARGE_INTEGER _counter;

    double        _startTime[255];
    double        _freq;

    double        _tickTime[255];
    double        _prevTickTime[255];

    double        _deltaTime[255];
    double        _prevDeltaTime[255];
  };
}

#endif