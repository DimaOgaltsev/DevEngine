#include <MainWindow.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpszCmdLine, int nCmdShow)
{
//debug info
#ifdef _DEBUG
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  MSG msg = {0};

  GUI::MainWindow mainWnd;
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