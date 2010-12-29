#include <MainWindow.h>

using namespace GUI;

MainWindow::MainWindow() :
  _hWnd(NULL),
  _hInst(NULL),
  _render(NULL)
{
}

MainWindow::~MainWindow()
{
  destroy();
}

void MainWindow::destroy()
{
  delete _render;
  CloseWindow(_hWnd);
  _render = NULL;
  _hWnd = NULL;
}

bool MainWindow::Create(HINSTANCE hInst, int PosX, int PosY, int Width, int Height)
{
  WNDCLASS WinClass;

  _hInst = hInst;

  WinClass.style          = 0;
  WinClass.lpfnWndProc    = WindowProc;
  WinClass.cbClsExtra     = 0;
  WinClass.cbWndExtra     = 0;
  WinClass.hInstance      = _hInst;
  WinClass.hIcon          = LoadIcon(_hInst, MAKEINTRESOURCE(IDI_APPLICATION));
  WinClass.hCursor        = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
  WinClass.hbrBackground  = (HBRUSH)0;
  WinClass.lpszMenuName   = 0;
  WinClass.lpszClassName  = NAME_WINDOWCLASS;

  if (!RegisterClass(&WinClass))
  {
    MessageBox(0, "Error registration window (MainWindow.cpp)", "Error:", MB_ICONERROR);
    return FALSE;
  }

  _hWnd = 
     CreateWindowEx( 
     WS_EX_CLIENTEDGE, NAME_WINDOWCLASS, NAME_WINDOWCLASS, 
     WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,
     PosX, PosY, Width, Height, 
     NULL, NULL, _hInst, (LPVOID)this
     );

  if (!_hWnd)
  {
    MessageBox(0, "Not _hWnd (MainWindow.cpp)", "Error:", MB_ICONERROR);
    return FALSE;
  }

  _render = new dev::Render(_hWnd);
  if (!_render->InitRender(0, 0, 0, true))
  {
    MessageBox(0, _render->GetLastError(), "Error:", MB_ICONERROR);
    return FALSE;
  }

  return TRUE;
}

LRESULT CALLBACK MainWindow::WindowProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
  switch(Message)
  {
  case WM_NCCREATE :
    {
      MainWindow* MainWnd = (MainWindow *)(((LPCREATESTRUCT)lParam)->lpCreateParams);
      MainWnd->_hWnd = hWnd;
      SetWindowLong(hWnd, GWL_USERDATA, (LONG)MainWnd);
      return TRUE;
    }
  default:
    {
      return ((MainWindow*)GetWindowLong(hWnd, GWL_USERDATA))->MsgProc(hWnd, Message, wParam, lParam);
    }
  }
}

LRESULT CALLBACK MainWindow::MsgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
  switch(Message)
  {
  case WM_KEYDOWN:
    {
      PostQuitMessage(0);
      break;
    }
  case WM_DESTROY:
    {
      PostQuitMessage(0);
      break;
    }
  }

  return DefWindowProc(hwnd, Message, wParam, lParam);
}
