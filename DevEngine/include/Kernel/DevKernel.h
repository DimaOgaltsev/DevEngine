#ifndef DEV_KERNEL_H
#define DEV_KERNEL_H

#include <Kernel/DevInclude.h>

namespace dev
{
  class Render
  {
  public:
    Render(HWND hWnd);
    virtual ~Render();

    bool  InitRender(int width, int height, int RefreshHz, bool FullScreenMode);
    void  Destroy();
    const char* GetLastError();

  protected:
    static void  startRender(LPVOID param);
    void  runRender();
    void  stopRender();

    HWND                  _hWnd;
    int                   _width, _height;

    HANDLE                _renderThread;
    bool                  _stopRender;

    LPDIRECT3D9           _directX;
    LPDIRECT3DDEVICE9     _deviceDX;
    D3DDISPLAYMODE        _display;
    D3DPRESENT_PARAMETERS _parametersD3D;
    std::string           _lastError;
  };
}

#endif