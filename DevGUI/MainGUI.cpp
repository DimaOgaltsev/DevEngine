/*#include <Kernel/DevRender.h>
#include <Model/DevMesh.h>
#include <Model/DevVertex.h>

void main(HINSTANCE hInstance, HINSTANCE, LPSTR lpszCmdLine, int nCmdShow)
{
  dev::Render* render = new dev::Render();
  if (!render->InitRender(0, 0, 0, false))
  {
    MessageBox(0, render->GetLastError(), "Error:", MB_ICONERROR);
    //TODO: Log file
    return;
  }

  dev::Camera* camera = 
    new dev::Camera(dev::Vec3(0, 0, -10), dev::Vec3(0, 0, 0), dev::Vec3(0, 1, 0), 
    D3DX_PI/4, (float)1.333f, 1.0f, 100.0f);

  dev::Scene* scene = new dev::Scene(camera);
  render->SetScene(scene);

  dev::Mesh* mesh = new dev::Mesh();
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
  mesh->SetVertices((dev::Vertex::Array)arrayVertex, 36, dev::Vertex::VT_PC32);

  const unsigned short arrayIndex[]=
  {
    0,1,2,    2,3,0,
    4,5,6,    6,7,4,
    8,9,10,   10,11,8,
    12,13,14, 14,15,12,
    16,17,18, 18,19,16,
    20,21,22, 22,23,20
  };
  mesh->SetIndexes((dev::Vertex::Array)arrayIndex, sizeof(arrayIndex), D3DFMT_INDEX16);
  scene->AddElement(mesh);
  mesh->SetRotation(dev::Vec3(45, 45, 0));

  render->Run();

  delete scene;
  delete camera;
  delete mesh;
  delete render;
}*/

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
    while(true)
    {
      while(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
      {
        if(!GetMessage(&msg, NULL, 0, 0))
          return (UINT)msg.wParam;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }

      mainWnd.Frame();
    }
  }

  return (UINT)msg.wParam;
}
