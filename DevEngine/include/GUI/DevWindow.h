#ifndef DEV_WINDOW_H
#define DEV_WINDOW_H

#include <Windows.h>
#include <Kernel/DevInclude.h>

namespace dev
{
  class Window
  {
  public:
    Window();
    virtual ~Window();

    HWND Create(HINSTANCE hInst, int PosX, int PosY, int Width, int Height);

  private:
    void destroy();

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK MsgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

    HINSTANCE    _hInst;
    HWND         _hWnd;

    int          _width;
    int          _height;

  };
}

#endif