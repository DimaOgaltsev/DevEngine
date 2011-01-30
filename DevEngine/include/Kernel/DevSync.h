#ifndef DEV_SYNC_H
#define DEV_SYNC_H

#include <Kernel/DevInclude.h>

namespace dev
{
  class CriticalSection
  {
  public:
    CriticalSection();
    virtual ~CriticalSection();

    void Lock();
    bool TryLock();
    void UnLock();

  protected:
    CRITICAL_SECTION _cs;
  };

  class Mutex
  {
  public:
    Mutex(const char* nameMutex);
    virtual ~Mutex();

    bool Lock();
    bool TryLock();
    void UnLock();

    inline const char* GetName()
    {
      return _name;
    }

  protected:
    HANDLE _mutex;
    const char* _name;
  };

  class Event
  {
  public:
    Event(const char* nameEvent);
    virtual ~Event();

    BOOL Set();
    BOOL Reset();
    bool Wait(DWORD time);

  protected:
    HANDLE _event;
  };

  class Semaphore
  {
  public:
    Semaphore(long numberRequests, const char* nameSemaphore);
    virtual ~Semaphore();

    bool Lock();
    bool TryLock();
    void UnLock();

    inline const char* GetName()
    {
      return _name;
    }

  protected:
    HANDLE _semaphore;
    const char* _name;
  };
}

#endif