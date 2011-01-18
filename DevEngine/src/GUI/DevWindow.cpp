#include <GUI/DevWindow.h>

using namespace dev;

Window::Window() :
  _hWnd(NULL),
  _hInst(NULL),
  _width(0),
  _height(0)
{
}

Window::~Window()
{
  destroy();
}

void Window::destroy()
{
  CloseWindow(_hWnd);
  _hWnd = NULL;
}

HWND Window::Create(HINSTANCE hInst, int PosX, int PosY, int Width, int Height)
{
  WNDCLASS WinClass;

  _hInst = hInst;
  _width = Width;
  _height = Height;

  WinClass.style          = 0;
  WinClass.lpfnWndProc    = WindowProc;
  WinClass.cbClsExtra     = 0;
  WinClass.cbWndExtra     = 0;
  WinClass.hInstance      = _hInst;
  WinClass.hIcon          = LoadIcon(_hInst, MAKEINTRESOURCE(IDI_APPLICATION));
  WinClass.hCursor        = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
  WinClass.hbrBackground  = (HBRUSH)0;
  WinClass.lpszMenuName   = 0;
  WinClass.lpszClassName  = "DevWindow";

  if (!RegisterClass(&WinClass))
  {
    MessageBox(0, "Error registration window (MainWindow.cpp)", "Error:", MB_ICONERROR);
    return FALSE;
  }

  _hWnd = 
    CreateWindowEx( 
    WS_EX_CLIENTEDGE, "DevWindow", "", 
    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
    PosX, PosY, Width, Height, 
    NULL, NULL, _hInst, (LPVOID)this
    );

  return _hWnd;
}

LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
  switch(Message)
  {
  case WM_NCCREATE :
    {
      Window* MainWnd = (Window *)(((LPCREATESTRUCT)lParam)->lpCreateParams);
      MainWnd->_hWnd = hWnd;
      SetWindowLong(hWnd, GWL_USERDATA, (LONG)MainWnd);
      return TRUE;
    }
  default:
    {
      return ((Window*)GetWindowLong(hWnd, GWL_USERDATA))->MsgProc(hWnd, Message, wParam, lParam);
    }
  }
}

LRESULT CALLBACK Window::MsgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
  switch(Message)
  {
  case WM_KEYDOWN:
    {
      if (wParam == VK_ESCAPE)
      {
        PostQuitMessage(0);
        break;
      }
    }
  case WM_DESTROY:
    {
      PostQuitMessage(0);
      break;
    }
  }

  return DefWindowProc(hwnd, Message, wParam, lParam);
}

