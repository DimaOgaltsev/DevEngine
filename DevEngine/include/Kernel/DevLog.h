#ifndef DEV_LOG_H
#define DEV_LOG_H

#include <Kernel/DevInsideLib.h>

namespace dev
{
  class Log
  {
  public:
    Log(const char* filename)
    {
      _fileLog = CreateFile(filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
      SystemTimer::GetTimer()->Reset(1);
    }
    virtual ~Log()
    {
      if (_fileLog)
        CloseHandle(_fileLog);
    }

    static Log* GetLog()
    {
      static Log* log = new Log("devEngine.log");;
      return log;
    }

    void WriteToLog(const char* textToLog)
    {
      if (_fileLog != INVALID_HANDLE_VALUE)
      {
        DWORD writedBytes;
        int secs = (int)SystemTimer::GetTimer()->GetTimeS(1);
        int mins = secs / 60;
        int hours = mins / 60;
        secs -= mins * 60;
        mins -= hours * 60;
        char time[255] = "";
        sprintf_s(time, 255, "[%i:%02i:%02i] : ", hours, mins, secs);
        WriteFile(_fileLog, time, strlen(time), &writedBytes, 0);
        WriteFile(_fileLog, textToLog, strlen(textToLog), &writedBytes, 0);
        WriteFile(_fileLog, "\r\n", 2, &writedBytes, 0);
      }
    }

  protected:
    HANDLE _fileLog;
  };
}

#endif