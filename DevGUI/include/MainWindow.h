#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <Windows.h>
#include <Kernel/DevKernel.h>

namespace GUI
{
#define NAME_WINDOWCLASS "MainWindow"

  class MainWindow
  {
  public:
    MainWindow();
    virtual ~MainWindow();

    bool Create(HINSTANCE hInst, int PosX, int PosY, int Width, int Height);

  private:
    void destroy();

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK MsgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

    dev::Render* _render;
    HINSTANCE    _hInst;
    HWND         _hWnd;

  };
}


#endif