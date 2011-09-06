#include <Kernel/DevInput.h>

#include <Kernel/DevInsideLib.h>
#pragma comment(lib, "winmm.lib")

#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC         ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE        ((USHORT) 0x02)
#endif
#ifndef HID_USAGE_GENERIC_KEYBOARD
#define HID_USAGE_GENERIC_KEYBOARD     ((USHORT) 0x06)
#endif

using namespace dev;

UINT      SizeRaw;
RAWINPUT* Raw;
//mouse
bool      Button[5];
double    MouseX, MouseY, MouseZ;
//keyboard
bool      Keys[256];

LRESULT CALLBACK HookProc(int code, WPARAM wParam, LPARAM lParam) 
{
  if (code < 0)
    return CallNextHookEx(0, code ,wParam , lParam);

  MSG* msg = (MSG*)lParam;
  if (msg->message == WM_INPUT)
  {
    GetRawInputData((HRAWINPUT)msg->lParam, RID_INPUT, (LPVOID)Raw, &SizeRaw, sizeof(RAWINPUTHEADER));

    switch(Raw->header.dwType)
    {
    case RIM_TYPEMOUSE:
      {
        MouseX += Raw->data.mouse.lLastX;
        MouseY += Raw->data.mouse.lLastY;

        if (Raw->data.mouse.usButtonFlags & RI_MOUSE_WHEEL)
          MouseZ += ((short)(Raw->data.mouse.usButtonData) < 0 ? -1 : 1);

        if (Raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_1_DOWN) Button[0] = true;
        if (Raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_1_UP)   Button[0] = false;

        if (Raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_2_DOWN) Button[1] = true;
        if (Raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_2_UP)   Button[1] = false;

        if (Raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_3_DOWN) Button[2] = true;
        if (Raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_3_UP)   Button[2] = false;

        if (Raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_4_DOWN) Button[3] = true;
        if (Raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_4_UP)   Button[3] = false;

        if (Raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_5_DOWN) Button[4] = true;
        if (Raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_5_UP)   Button[4] = false;

        break;
      }
    case RIM_TYPEKEYBOARD:
      {
        if (Raw->data.keyboard.Flags & RI_KEY_BREAK)
          Keys[Raw->data.keyboard.MakeCode & 0xff] = false; 
        else
          Keys[Raw->data.keyboard.MakeCode & 0xff] = true;
        break;
      }
    }
    return TRUE;
  }
  return CallNextHookEx(0, code, wParam , lParam); 
};

Input::Input(bool mouse, bool keyboard) :
  _hook(NULL),
  _keyboard(keyboard),
  _mouse(mouse)
{
  Raw = new RAWINPUT();
  SizeRaw = sizeof(RAWINPUT);

  OnInput(mouse, keyboard); 
}

Input::~Input()
{
  OffInput();
}

void Input::OnInput(bool mouse, bool keyboard)
{
  if (!mouse && !keyboard)
    return;

  _mouse = mouse;
  _keyboard = keyboard;

  RAWINPUTDEVICE Rid[1];
  Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC; 
  Rid[0].dwFlags     = 0;   
  Rid[0].hwndTarget  = 0;
  //mouse
  if (mouse)
  {
    Rid[0].usUsage   = HID_USAGE_GENERIC_MOUSE;
    RegisterRawInputDevices(Rid, 1, sizeof(RAWINPUTDEVICE));
    ZeroMemory(&Button, 5 * sizeof(bool));
    MouseX = 0; MouseY = 0; MouseZ = 0;
  }
  //keyboard
  if (keyboard)
  {
    Rid[0].usUsage   = HID_USAGE_GENERIC_KEYBOARD;
    RegisterRawInputDevices(Rid, 1, sizeof(RAWINPUTDEVICE));
    ZeroMemory(&Keys, 256 * sizeof(bool));
  }

  _hook = SetWindowsHookEx(WH_GETMESSAGE, HookProc, 0, GetCurrentThreadId());
}

void Input::OffInput()
{
  if (!_mouse && !_keyboard)
    return;

  if (_hook)
  {
    UnhookWindowsHookEx(_hook);
    _hook = NULL;
  }

  RAWINPUTDEVICE Rid[1];
  Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC; 
  Rid[0].dwFlags     = RIDEV_REMOVE;   
  Rid[0].hwndTarget  = 0;
  //mouse
  if (_mouse)
  {
    Rid[0].usUsage   = HID_USAGE_GENERIC_MOUSE;
    RegisterRawInputDevices(Rid, 1, sizeof(RAWINPUTDEVICE));
    ZeroMemory(&Button, 5 * sizeof(bool));
    MouseX = 0; MouseY = 0; MouseZ = 0;
    _mouse = FALSE;
  }
  //keyboard
  if (_keyboard)
  {
    Rid[0].usUsage   = HID_USAGE_GENERIC_KEYBOARD;
    RegisterRawInputDevices(Rid, 1, sizeof(RAWINPUTDEVICE));
    ZeroMemory(&Keys, 256 * sizeof(bool));
    _keyboard = FALSE;
  }
}

//mouse
bool Input::GetClickMouseButton(int button) const
{
  return Button[button];
}

double Input::GetMouseDeltaX() const
{
  double mx = MouseX;
  MouseX = 0;
  return mx;
}

double Input::GetMouseDeltaY() const
{
  double my = MouseY;
  MouseY = 0;
  return my;
}

double Input::GetMouseDeltaZ() const
{
  double mz = MouseZ;
  MouseZ = 0;
  return mz;
}

//KeyBoard
bool Input::GetKeyPressed(byte SC_KEY) const
{
  return Keys[SC_KEY];
}

