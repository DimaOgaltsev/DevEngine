#include <Kernel/DevKernel.h>

using namespace DevEngine;

DevRender::DevRender(HWND hWnd):
  _hWnd(hWnd),
  _directX(NULL),
  _deviceDX(NULL),
  _width(0),
  _height(0),
  _stopRender(false),
  _lastError(NULL)
{
}

DevRender::~DevRender()
{
  Destroy();
  _lastError = NULL;
}

bool DevRender::InitRender(int width, int height, int RefreshHz, bool FullScreenMode)
{
  if (!_directX)
    if (!(_directX = Direct3DCreate9(D3D_SDK_VERSION)))
    {
      _lastError = "Failed init Direct3D (DevKernel.cpp)";
      return false;
    }

  ZeroMemory(&_display ,sizeof(_display));
  if (FAILED(_directX->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &_display)))
  {
    _lastError = "Failed init DisplayMode (DevKernel.cpp)";
    return false;
  }

  if (FullScreenMode)
  {
    _width = _display.Width;
    _height = _display.Height;
  }
  else
    if ((!width) || (!height))
    {
      RECT rect;
      GetClientRect(_hWnd, &rect);
      _width  = rect.right - rect.left;
      _height = rect.bottom - rect.top;
    }
    else
    {
      _width = width;
      _height = height;
    }

  ZeroMemory(&_parametersD3D ,sizeof(_parametersD3D));
  if (FullScreenMode)
  {
    if (RefreshHz > 0) 
      _parametersD3D.FullScreen_RefreshRateInHz = RefreshHz;
    else 
      _parametersD3D.FullScreen_RefreshRateInHz = _display.RefreshRate;
  }

  _parametersD3D.BackBufferCount           = 0;
  _parametersD3D.BackBufferWidth           = _width;
  _parametersD3D.BackBufferHeight          = _height;
  _parametersD3D.Windowed                  = !FullScreenMode;
  _parametersD3D.SwapEffect                = D3DSWAPEFFECT_DISCARD;
  _parametersD3D.BackBufferFormat          = _display.Format;
  _parametersD3D.EnableAutoDepthStencil    = true;
  _parametersD3D.AutoDepthStencilFormat    = D3DFMT_D24S8;
  _parametersD3D.PresentationInterval      = D3DPRESENT_INTERVAL_ONE;
  _parametersD3D.MultiSampleType          = D3DMULTISAMPLE_4_SAMPLES;

  if (FAILED(_directX->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd,
    D3DCREATE_HARDWARE_VERTEXPROCESSING, &_parametersD3D, &_deviceDX)))
  {
    _lastError = "Failed device Direct3D (DirectMain.cpp)";
    return false;
  }

  _deviceDX->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
  _deviceDX->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

  DWORD RenderThreadID;
  //_renderThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartRender, this, 0, &RenderThreadID);

  return true;
}

void DevRender::Destroy()
{
  if (_deviceDX)
    _deviceDX->Release();
  if (_directX)
    _directX->Release();
}

char* DevRender::GetLastError()
{
  return _lastError;
}
