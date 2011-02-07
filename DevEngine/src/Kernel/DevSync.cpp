#include <Kernel/DevSync.h>

using namespace dev;

CriticalSection::CriticalSection()
{
  InitializeCriticalSection(&_cs);
}

CriticalSection::~CriticalSection()
{
  DeleteCriticalSection(&_cs);
}

void CriticalSection::Lock()
{
  EnterCriticalSection(&_cs);
}

bool CriticalSection::TryLock()
{
  return (TryEnterCriticalSection(&_cs) != 0);
}

void CriticalSection::UnLock()
{
  LeaveCriticalSection(&_cs);
}

Mutex::Mutex(const char* nameMutex)
{
  _name = nameMutex;
  _mutex = NULL;
  _mutex = CreateMutex(0, false, _name);
}

Mutex::~Mutex()
{
  CloseHandle(_mutex);
  _mutex = NULL;
}

bool Mutex::Lock()
{
  return (WaitForSingleObject(_mutex, INFINITE) == WAIT_OBJECT_0);
}

bool Mutex::TryLock()
{
  return (WaitForSingleObject(_mutex, 0) == WAIT_OBJECT_0);
}

void Mutex::UnLock()
{
  ReleaseMutex(_mutex);
}


Event::Event(const char* nameEvent)
{
  _event = CreateEvent(0, false, false, nameEvent);
}

Event::~Event()
{
  CloseHandle(_event);
}

BOOL Event::Set()
{
  return SetEvent(_event);
}

BOOL Event::Reset()
{
  return ResetEvent(_event);
}

bool Event::Wait(DWORD time)
{
  return (WaitForSingleObject(_event, time) == WAIT_OBJECT_0);
}

Semaphore::Semaphore(long numberRequests, const char* nameSemaphore)
{
  _semaphore = CreateSemaphore(0, numberRequests, numberRequests, nameSemaphore);
}

Semaphore::~Semaphore()
{
  CloseHandle(_semaphore);
}

bool Semaphore::Lock()
{
  return (WaitForSingleObject(_semaphore, INFINITE) == WAIT_OBJECT_0);
}

bool Semaphore::TryLock()
{
  return (WaitForSingleObject(_semaphore, 0) == WAIT_OBJECT_0);
}

void Semaphore::UnLock()
{
  ReleaseSemaphore(_semaphore, 1, 0);
}
