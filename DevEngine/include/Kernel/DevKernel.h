#ifndef DEV_KERNEL_H
#define DEV_KERNEL_H

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace DevEngine
{
  class DevRender
  {
  public:
    DevRender(HWND hWnd);
    virtual ~DevRender();

    bool  InitRender(int width, int height, int RefreshHz, bool FullScreenMode);
    void  Destroy();
    char* GetLastError();

  protected:
    HWND                  _hWnd;
    int                   _width, _height;
    bool                  _stopRender;
    LPDIRECT3D9           _directX;
    LPDIRECT3DDEVICE9     _deviceDX;
    D3DDISPLAYMODE        _display;
    D3DPRESENT_PARAMETERS _parametersD3D;
    char*                 _lastError;
  };
}

#endif