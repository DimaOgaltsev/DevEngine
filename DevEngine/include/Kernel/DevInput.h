#ifndef DEV_INPUT_H
#define DEV_INPUT_H

#include <Kernel/DevInclude.h>
#include <Kernel/DevScanCodes.h>
#include <Kernel/DevSingleton.h>

namespace dev
{
  class Input
  {
  public:
    Input(bool mouse = true, bool keyboard = true);
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

  protected:
    bool      _mouse;
    bool      _keyboard;
    HHOOK     _hook;
  };
}

#endif