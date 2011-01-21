#include <MainWindow.h>

using namespace GUI;

MainWindow::MainWindow() :
  _hWnd(NULL),
  _hInst(NULL),
  _render(NULL),
  _input(NULL),
  _camera(NULL),
  _scene(NULL),
  _mesh(NULL),
  _width(0),
  _height(0)
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
  if (!_render->InitRender(0, 0, 0, false))
  {
    MessageBox(0, _render->GetLastError(), "Error:", MB_ICONERROR);
    return FALSE;
  }

  LoadScene();

  _render->Run();

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
      if (wParam == VK_ESCAPE)
      {
        SendMessage(hwnd, WM_DESTROY, 0, 0);
        break;
      }
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

void MainWindow::LoadScene()
{
  _mesh = new dev::Mesh();
  dev::Vertex::VertexPC32 arrayVertex[] = 
  {
    {1.0f,  0.0f,  0.0f, D3DCOLOR_XRGB(255,   0,    0)},
    {1.0f,  1.0f,  0.0f, D3DCOLOR_XRGB(255, 255,    0)},
    {0.0f,  1.0f,  0.0f, D3DCOLOR_XRGB(  0, 255,    0)},
    {0.0f,  0.0f,  0.0f, D3DCOLOR_XRGB(  0,   0,    0)},

    {0.0f,  0.0f,  0.0f, D3DCOLOR_XRGB(  0,   0,    0)},
    {0.0f,  1.0f,  0.0f, D3DCOLOR_XRGB(  0, 255,    0)},
    {0.0f,  1.0f,  1.0f, D3DCOLOR_XRGB(  0, 255,  255)},
    {0.0f,  0.0f,  1.0f, D3DCOLOR_XRGB(  0,   0,  255)},

    {0.0f,  0.0f,  1.0f, D3DCOLOR_XRGB(  0,   0,  255)},
    {0.0f,  1.0f,  1.0f, D3DCOLOR_XRGB(  0, 255,  255)},
    {1.0f,  1.0f,  1.0f, D3DCOLOR_XRGB(255, 255,  255)},
    {1.0f,  0.0f,  1.0f, D3DCOLOR_XRGB(255,   0,  255)},

    {1.0f,  0.0f,  1.0f, D3DCOLOR_XRGB(255,   0,  255)},
    {1.0f,  1.0f,  1.0f, D3DCOLOR_XRGB(255, 255,  255)},
    {1.0f,  1.0f,  0.0f, D3DCOLOR_XRGB(255, 255,    0)},
    {1.0f,  0.0f,  0.0f, D3DCOLOR_XRGB(255,   0,    0)},

    {1.0f,  0.0f,  0.0f, D3DCOLOR_XRGB(255,   0,    0)},
    {0.0f,  0.0f,  0.0f, D3DCOLOR_XRGB(0,     0,    0)},
    {0.0f,  0.0f,  1.0f, D3DCOLOR_XRGB(255, 255,  255)},
    {1.0f,  0.0f,  1.0f, D3DCOLOR_XRGB(255,   0,  255)},

    {1.0f,  1.0f,  1.0f, D3DCOLOR_XRGB(255, 255,  255)},
    {0.0f,  1.0f,  1.0f, D3DCOLOR_XRGB(  0, 255,  255)},
    {0.0f,  1.0f,  0.0f, D3DCOLOR_XRGB(  0, 255,    0)},
    {1.0f,  1.0f,  0.0f, D3DCOLOR_XRGB(255, 255,    0)}
  };
  _mesh->SetVertices((dev::Vertex::Array)arrayVertex, 36, dev::Vertex::VT_PC32);

  const unsigned short arrayIndex[] =
  {
    0,1,2,    2,3,0,
    4,5,6,    6,7,4,
    8,9,10,   10,11,8,
    12,13,14, 14,15,12,
    16,17,18, 18,19,16,
    20,21,22, 22,23,20
  };
  _mesh->SetIndexes((dev::Vertex::Array)arrayIndex, sizeof(arrayIndex), D3DFMT_INDEX16);
  _mesh->SetRotation(D3DXVECTOR3(45, 45, 0));

  _camera = 
    new dev::Camera(D3DXVECTOR3(0, 0, -10), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0), 
    D3DX_PI/4, (float)_width/_height, 1.0f, 250.0f);

  _scene = new dev::Scene(_camera);
  _render->SetScene(_scene);
  _scene->AddElement(_mesh);
  
  _input = new dev::Input(true, true);
  _input->StartInputThread(10, MainWindow::Func, this);
  ShowCursor(FALSE);
}

void MainWindow::Func(LPVOID param, double deltaTime)
{
  MainWindow* mw = (MainWindow*)param;
  if (mw)
    mw->InputFunc(deltaTime);
}

void MainWindow::InputFunc(double deltaTime)
{
  double mouseX = _input->GetMouseDeltaX() * deltaTime;
  double mouseY = _input->GetMouseDeltaY() * deltaTime;
  double mouseZ = _input->GetMouseDeltaY() * deltaTime;

  if (_input->GetKeyPressed(SC_W))
    _camera->SetPosition(_camera->GetPosition() + D3DXVECTOR3(0, 0, 1));
  if (_input->GetKeyPressed(SC_S))
    _camera->SetPosition(_camera->GetPosition() + D3DXVECTOR3(0, 0, -1));
  if (_input->GetKeyPressed(SC_D))
    _camera->SetPosition(_camera->GetPosition() + D3DXVECTOR3(1, 0, 0));
  if (_input->GetKeyPressed(SC_A))
    _camera->SetPosition(_camera->GetPosition() + D3DXVECTOR3(-1, 0, 0));
  if (_input->GetKeyPressed(SC_Q))
    _camera->SetPosition(_camera->GetPosition() + D3DXVECTOR3(0, 1, 0));
  if (_input->GetKeyPressed(SC_Z))
    _camera->SetPosition(_camera->GetPosition() + D3DXVECTOR3(0, -1, 0));
  if (_input->GetKeyPressed(SC_NUMPAD4))
    _mesh->SetPosition(_mesh->GetPosition() + D3DXVECTOR3(-1, 0, 0));
  if (_input->GetKeyPressed(SC_NUMPAD2))
    _mesh->SetPosition(_mesh->GetPosition() + D3DXVECTOR3(0, 0, -1));
  if (_input->GetKeyPressed(SC_NUMPAD6))
    _mesh->SetPosition(_mesh->GetPosition() + D3DXVECTOR3(1, 0, 0));
  if (_input->GetKeyPressed(SC_NUMPAD8))
    _mesh->SetPosition(_mesh->GetPosition() + D3DXVECTOR3(0, 0, 1));
}
