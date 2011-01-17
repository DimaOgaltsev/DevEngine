#include <Kernel/DevRender.h>

using namespace dev;

Render::Render(HWND hWnd):
  _hWnd(hWnd),
  _directX(NULL),
  _deviceDX(NULL),
  _width(0),
  _height(0),
  _stopRender(false),
  _lastError("")
{
}

Render::~Render()
{
  Destroy();
}

void Render::Destroy()
{
  stopRender();
  if (_renderThread)
    WaitForSingleObject(_renderThread, 10000);
  _lastError.clear();
  if (_deviceDX)
    _deviceDX->Release();
  if (_directX)
    _directX->Release();
}

const char* Render::GetLastError()
{
  return _lastError.c_str();
}

bool Render::InitRender(int width, int height, int RefreshHz, bool FullScreenMode)
{
  if (!_directX)
    if (!(_directX = Direct3DCreate9(D3D_SDK_VERSION)))
    {
      _lastError = "Failed init Direct3D (DevRender.cpp)";
      return false;
    }

  ZeroMemory(&_display ,sizeof(_display));
  if (FAILED(_directX->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &_display)))
  {
    _lastError = "Failed init DisplayMode (DevRender.cpp)";
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
  _parametersD3D.MultiSampleType           = D3DMULTISAMPLE_NONE;

  if (FAILED(_directX->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd,
    D3DCREATE_HARDWARE_VERTEXPROCESSING, &_parametersD3D, &_deviceDX)))
  {
    _lastError = "Failed device Direct3D (DirectMain.cpp)";
    return false;
  }

  _deviceDX->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
  _deviceDX->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

  DWORD RenderThreadID;
  _renderThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)startRender, (LPVOID)this, 0, &RenderThreadID);

  return true;
}

Scene* Render::GetScene()
{
  return _scene;
}

void Render::SetScene(Scene* scene)
{
  scene->SetDevice(_deviceDX);
  _scene = scene;
}

void Render::startRender(LPVOID param)
{
  Render* _render = (Render*)param;
  if (_render)
    _render->runRender();
}

void Render::runRender()
{
  if (!_deviceDX)
    return;

  //TODO: перенести в GUI часть
  dev::Camera* camera = 
    new dev::Camera(D3DXVECTOR3(0, 0, -10), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0), 
                    D3DX_PI/4, (float)_width/_height, 1.0f, 100.0f);
  dev::Scene* scene = new dev::Scene(camera);
  SetScene(scene);

  
  
  
  LPDIRECT3DVERTEXBUFFER9 pBufferVershin				=	NULL;
    LPDIRECT3DINDEXBUFFER9	pBufferIndex				=	NULL;
    struct CUSTOMVERTEX
    {
      FLOAT X,Y,Z;
      FLOAT nx,ny,nz;
      FLOAT tu,tv;
    };
  #define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)
    const unsigned short Index[]=
    {
      0,1,2,		2,3,0,
      4,5,6,		6,7,4,
      8,9,10,		10,11,8,
      12,13,14,	14,15,12,
      16,17,18,	18,19,16,
      20,21,22,	22,23,20
    };
  
    CUSTOMVERTEX Vershin[] =
    {
      {1.0f,	0.0f,		0.0f,		0.0f,		0.0f,		-1.0f,	1.0f,		1.0f},
      {1.0f,	1.0f,		0.0f,		0.0f,		0.0f,		-1.0f,	0.0f,		1.0f},
      {0.0f,	1.0f,		0.0f,		0.0f,		0.0f,		-1.0f,	0.0f,		0.0f},
      {0.0f,	0.0f,		0.0f,		0.0f,		0.0f,		-1.0f,	1.0f,		0.0f},
  
      {0.0f,	0.0f,		0.0f,		-1.0f,	0.0f,		0.0f,		1.0f,		1.0f},
      {0.0f,	1.0f,		0.0f,		-1.0f,	0.0f,		0.0f,		0.0f,		1.0f},
      {0.0f,	1.0f,		1.0f,		-1.0f,	0.0f,		0.0f,		0.0f,		0.0f},
      {0.0f,	0.0f,		1.0f,		-1.0f,	0.0f,		0.0f,		1.0f,		0.0f},
  
      {0.0f,	0.0f,		1.0f,		0.0f,		0.0f,		1.0f,		1.0f,		1.0f},
      {0.0f,	1.0f,		1.0f,		0.0f,		0.0f,		1.0f,		0.0f,		1.0f},
      {1.0f,	1.0f,		1.0f,		0.0f,		0.0f,		1.0f,		0.0f,		0.0f},
      {1.0f,	0.0f,		1.0f,		0.0f,		0.0f,		1.0f,		1.0f,		0.0f},
  
      {1.0f,	0.0f,		1.0f,		1.0f,		0.0f,		0.0f,		1.0f,		1.0f},
      {1.0f,	1.0f,		1.0f,		1.0f,		0.0f,		0.0f,		0.0f,		1.0f},
      {1.0f,	1.0f,		0.0f,		1.0f,		0.0f,		0.0f,		0.0f,		0.0f},
      {1.0f,	0.0f,		0.0f,		1.0f,		0.0f,		0.0f,		1.0f,		0.0f},
  
      {1.0f,	0.0f,		0.0f,		0.0f,		-1.0f,	0.0f,		1.0f,		1.0f},
      {0.0f,	0.0f,		0.0f,		0.0f,		-1.0f,	0.0f,		0.0f,		1.0f},
      {0.0f,	0.0f,		1.0f,		0.0f,		-1.0f,	0.0f,		0.0f,		0.0f},
      {1.0f,	0.0f,		1.0f,		0.0f,		-1.0f,	0.0f,		1.0f,		0.0f},
  
      {1.0f,	1.0f,		1.0f,		0.0f,		1.0f,		0.0f,		1.0f,		1.0f},
      {0.0f,	1.0f,		1.0f,		0.0f,		1.0f,		0.0f,		0.0f,		1.0f},
      {0.0f,	1.0f,		0.0f,		0.0f,		1.0f,		0.0f,		0.0f,		0.0f},
      {1.0f,	1.0f,		0.0f,		0.0f,		1.0f,		0.0f,		1.0f,		0.0f}
    };
  
    (_deviceDX->CreateVertexBuffer(		36*sizeof(CUSTOMVERTEX),0,
      D3DFVF_CUSTOMVERTEX,
      D3DPOOL_DEFAULT,
      &pBufferVershin, NULL));
    (_deviceDX->CreateIndexBuffer(		36*sizeof(Index),0,
      D3DFMT_INDEX16,
      D3DPOOL_DEFAULT,
      &pBufferIndex,NULL));
    void* pBV;
    void* pBI;
    FAILED(pBufferVershin->Lock (0, sizeof(Vershin), (void**)&pBV, 0));
    memcpy(pBV,Vershin,sizeof(Vershin));
    pBufferVershin->Unlock();
  
    FAILED(pBufferIndex->Lock (0, sizeof(Index), (void**)&pBI, 0));
    memcpy(pBI,Index,sizeof(Index));
    pBufferIndex->Unlock();
  

  while(!_stopRender)
  {
    _deviceDX->Clear(0, 0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(153, 153, 255), 1.0f, 0);
    _deviceDX->BeginScene();

    _scene->Update();

    
    _deviceDX->SetStreamSource(0,pBufferVershin,0,sizeof(CUSTOMVERTEX));
    _deviceDX->SetFVF(D3DFVF_CUSTOMVERTEX);
    _deviceDX->SetIndices(pBufferIndex);
    _deviceDX->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,36,0,12);
    

    _deviceDX->EndScene();
    _deviceDX->Present(0, 0, 0, 0);
  }
}

void Render::stopRender()
{
  _stopRender = true;
}

