#include <MainWindow.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpszCmdLine, int nCmdShow)
{
  MSG msg = {0};

  DevGUI::MainWindow mainWnd;
  if (mainWnd.Create(hInstance, 0, 0, 800, 600))
  {
    while (GetMessage(&msg, NULL, 0, 0))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return (UINT)msg.wParam;
}