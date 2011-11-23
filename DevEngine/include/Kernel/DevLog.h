#ifndef DEV_LOG_H
#define DEV_LOG_H

#include <Kernel/DevInsideLib.h>

namespace dev
{
  class Log
  {
  public:
    static Log* GetLog()
    {
      static Log* log = new Log(logFilename);
      return log;
    }

    void WriteToLog(const char* textToLog)
    {
      if (_fileLog != INVALID_HANDLE_VALUE)
      {
        DWORD writedBytes;
        int secs = (int)SystemTimer::Get()->GetTimeS(1);
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
    Log(const char* filename)
    {
      _fileLog = CreateFile(filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
      SystemTimer::Get()->Reset(1);
    }
    virtual ~Log()
    {
      if (_fileLog)
        CloseHandle(_fileLog);
    }

    HANDLE _fileLog;
  };
}

#endif