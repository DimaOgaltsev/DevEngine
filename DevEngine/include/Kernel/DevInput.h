#ifndef DEV_INPUT_H
#define DEV_INPUT_H

#include <Kernel/DevInclude.h>
#include <Kernel/DevScanCodes.h>

namespace dev
{
  class Input
  {
  public:
    Input();
    Input(bool mouse, bool keyboard);
    virtual ~Input();

    void OnInput(bool mouse, bool keyboard);
    void OffInput();

    //mouse
    bool GetClickMouseButton(int button) const;
    double GetMouseDeltaX() const;
    double GetMouseDeltaY() const;
    double GetMouseDeltaZ() const;

    //keyboard
    bool GetKeyPressed(byte SC_KEY) const;

    typedef void (*InputFunc)(LPVOID param, double deltaTimeMS);

    void StartInputThread(int time, InputFunc inputFunc, LPVOID param);
    void StopInputThread();

  protected:
    bool      _mouse;
    bool      _keyboard;
    HHOOK     _hook;

    static void inputThreadRun(LPVOID param);
    void        inputThread();
    
    HANDLE    _inputThread;
    int       _requestTime;
    LPVOID    _param;
    InputFunc _func;
    bool      _stopInputThread;
  };
}

#endif